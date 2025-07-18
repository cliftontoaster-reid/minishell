# Tools Directory

This directory contains testing and utility scripts for the minishell project.

## Files

### `tests.ts`

A comprehensive test suite written in TypeScript for Deno that tests the minishell with Valgrind for memory leak detection.

**Features:**

- Tests all built-in commands (echo, cd, pwd, export, unset, env, exit)
- Tests pipes and redirections
- Tests variable expansion
- Tests error handling
- Tests memory leak detection with Valgrind
- Generates detailed JSON and HTML reports
- Covers edge cases and stress testing

**Usage:**

```bash
# Run with Deno directly
deno run --allow-run --allow-read --allow-write tools/tests.ts

# Or use the wrapper script
./tools/run_tests.sh
```

### `run_tests.sh`

A bash wrapper script that builds the minishell before running the test suite.

**Usage:**

```bash
./tools/run_tests.sh
```

## Test Categories

The test suite includes the following categories:

### 1. Built-in Commands

- `echo` with various flags and arguments
- `pwd` for current directory
- `env` for environment variables
- `cd` for directory changes
- `export` for setting environment variables
- `unset` for removing environment variables
- `exit` with various exit codes

### 2. Variable Expansion

- Basic variable expansion (`$VAR`)
- Path variable expansion (`$PATH`)
- Exit status expansion (`$?`)
- Non-existent variable handling

### 3. Pipes and Redirections

- Basic pipes (`|`)
- Multiple pipes
- Output redirection (`>`)
- Append redirection (`>>`)
- Input redirection (`<`)
- Complex combinations

### 4. Error Handling

- Command not found errors
- Invalid syntax errors
- Permission errors
- Memory allocation errors

### 5. Edge Cases

- Empty commands
- Long command lines
- Many arguments
- Special characters
- Quoting (single and double quotes)
- Mixed quotes with variable expansion

### 6. Memory Testing

- Memory leak detection with Valgrind
- Stress testing with large environments
- Deep pipe chains
- Large argument lists

## Output

The test suite generates:

- Console output with real-time test results
- `test_report.json` - Detailed JSON report
- `test_report.html` - Interactive HTML report

## Requirements

- Deno (<https://deno.land/>)
- Valgrind
- A built minishell executable
- readline.supp file for Valgrind suppressions

## Example Output

```
🚀 Starting minishell test suite with Valgrind...

📋 Running 45 tests...

🔍 Testing: simple_echo
   Description: Test basic echo command
   Command: echo hello world
   ✅ PASSED

🔍 Testing: echo_with_newline
   Description: Test echo with -n flag
   Command: echo -n hello world
   ✅ PASSED

...

============================================================
📊 TEST RESULTS SUMMARY
============================================================
Total tests: 45
Passed: 43
Failed: 2
Success rate: 95.6%

✅ Test suite completed!
```

## Customization

You can easily add more test cases by modifying the `getTestCases()` method in `tests.ts`. Each test case should follow this interface:

```typescript
interface TestCase {
  name: string; // Unique test identifier
  command: string; // Command to execute
  expectedExitCode?: number; // Expected exit code (default: 0)
  expectMemoryLeaks?: boolean; // Whether memory leaks are expected
  description?: string; // Human-readable description
}
```
