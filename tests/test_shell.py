"""Run real shell processes to check execution, PATH, and failure recovery."""
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
BINARY = Path(os.environ.get("SHELL_BINARY", str(ROOT / "hsh"))).resolve()


class ShellTests(unittest.TestCase):
    def run_shell(self, commands, *, path=None, cwd=None):
        env = os.environ.copy()
        if path is not None:
            env["PATH"] = path
        return subprocess.run(
            [str(BINARY)], input=commands, text=True, capture_output=True,
            timeout=5, env=env, cwd=cwd,
        )

    def test_absolute_commands_keep_shell_alive(self):
        result = self.run_shell("/bin/echo first\n/bin/echo second\n")
        self.assertEqual(result.stdout, "first\nsecond\n")
        self.assertEqual(result.returncode, 0)

    def test_path_lookup(self):
        self.assertEqual(self.run_shell("echo hello\n", path="/bin").stdout, "hello\n")

    def test_relative_executable(self):
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "hello"
            executable.write_text("#!/bin/sh\nprintf 'relative\\n'\n")
            executable.chmod(0o700)
            self.assertEqual(self.run_shell("./hello\n", cwd=directory).stdout, "relative\n")

    def test_empty_path_entry_is_current_directory(self):
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "hello"
            executable.write_text("#!/bin/sh\nprintf 'local\\n'\n")
            executable.chmod(0o700)
            self.assertEqual(self.run_shell("hello\n", path=":/bin", cwd=directory).stdout, "local\n")

    def test_more_than_64_path_entries(self):
        path = ":".join(["/missing"] * 100 + ["/bin"])
        self.assertEqual(self.run_shell("echo found\n", path=path).stdout, "found\n")

    def test_more_than_64_arguments(self):
        words = [str(i) for i in range(100)]
        result = self.run_shell("/bin/echo " + " ".join(words) + "\n")
        self.assertEqual(result.stdout, " ".join(words) + "\n")

    def test_blank_lines_and_tabs(self):
        self.assertEqual(self.run_shell("\n \t\n/bin/echo\thello\n").stdout, "hello\n")

    def test_missing_command_status(self):
        result = self.run_shell("no_such_command_gerald\n", path="/bin")
        self.assertEqual(result.returncode, 127)
        self.assertIn("not found", result.stderr)

    def test_missing_absolute_command_recovers(self):
        result = self.run_shell("/no/such/command\n/bin/echo recovered\n")
        self.assertEqual(result.stdout, "recovered\n")
        self.assertEqual(result.returncode, 0)

    def test_child_exec_failure_does_not_start_second_shell(self):
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "broken"
            executable.write_text("not an executable format\n")
            executable.chmod(0o700)
            result = self.run_shell("./broken\n/bin/echo recovered\n", cwd=directory)
            self.assertEqual(result.stdout, "recovered\n")
            self.assertEqual(result.returncode, 0)

    def test_permission_denied_status(self):
        with tempfile.TemporaryDirectory() as directory:
            executable = Path(directory) / "blocked"
            executable.write_text("#!/bin/sh\nexit 0\n")
            executable.chmod(0o600)
            self.assertEqual(self.run_shell("./blocked\n", cwd=directory).returncode, 126)

    def test_exit_preserves_last_status(self):
        result = self.run_shell("/bin/false\nexit\n/bin/echo unreachable\n")
        self.assertEqual(result.returncode, 1)
        self.assertEqual(result.stdout, "")

    def test_environment_builtin(self):
        result = self.run_shell("env\n", path="/missing")
        self.assertIn("PATH=/missing\n", result.stdout)
        self.assertEqual(result.returncode, 0)

    def test_eof_is_quiet(self):
        result = self.run_shell("")
        self.assertEqual(result.stdout, "")
        self.assertEqual(result.returncode, 0)


if __name__ == "__main__":
    unittest.main()
