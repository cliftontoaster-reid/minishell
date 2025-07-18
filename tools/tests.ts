#!/usr/bin/env deno run --allow-run --allow-read --allow-write

/**
 * Comprehensive test suite for minishell using Valgrind
 *
 * This script tests various aspects of the minishell implementation:
 * - Built-in commands (echo, cd, pwd, export, unset, env, exit)
 * - Pipes and redirections
 * - Variable expansion
 * - Error handling
 * - Memory leaks detection with Valgrind
 *
 * Usage: deno run --allow-run --allow-read --allow-write tools/tests.ts
 */

import { exists } from "https://deno.land/std@0.208.0/fs/mod.ts";
import { join } from "https://deno.land/std@0.208.0/path/mod.ts";

interface TestCase {
  name: string;
  command: string;
  expectedExitCode?: number;
  expectMemoryLeaks?: boolean;
  description?: string;
  expectedOutput?: string[]; // Array of strings that should be present in output
  expectedOutputContains?: string[]; // Array of strings that should be contained in output
  expectedOutputExact?: string; // Exact output match (useful for simple commands)
  shouldNotContain?: string[]; // Array of strings that should NOT be present in output
}

interface TestResult {
  name: string;
  passed: boolean;
  exitCode: number;
  hasMemoryLeaks: boolean;
  valgrindOutput: string;
  actualOutput: string;
  outputValidation: {
    passed: boolean;
    details: string[];
  };
  failureReasons: string[];
  error?: string;
}

class MinishellTester {
  private minishellPath: string;
  private suppressionsPath: string;
  private testResults: TestResult[] = [];
  private passedTests = 0;
  private failedTests = 0;

  constructor() {
    this.minishellPath = "./minishell";
    this.suppressionsPath = "./readline.supp";
  }

  async init(): Promise<boolean> {
    // Recompile minishell
    const makeProcess = new Deno.Command("make", {
      args: ["re"],
      stdout: "piped",
      stderr: "piped",
    });
    const { code, stdout, stderr } = await makeProcess.output();

    if (code !== 0) {
      console.error("❌ Failed to rebuild minishell:");
      console.error(new TextDecoder().decode(stderr));
      return false;
    }

    console.log(new TextDecoder().decode(stdout));
    // Check if minishell executable exists
    if (!(await exists(this.minishellPath))) {
      console.error(
        "❌ minishell executable not found. Please run 'make' first.",
      );
      return false;
    }

    // Check if readline suppressions file exists
    if (!(await exists(this.suppressionsPath))) {
      console.error("❌ readline.supp file not found.");
      return false;
    }

    console.log("🚀 Starting minishell test suite with Valgrind...\n");
    return true;
  }

  private parseMemoryLeaks(valgrindOutput: string): boolean {
    // Parse Valgrind output to check for actual memory leaks
    // Look for the leak summary section and extract the numbers
    const leakSummaryMatch = valgrindOutput.match(
      /LEAK SUMMARY:(.*?)(?=\n==|\n\n|$)/s,
    );
    if (!leakSummaryMatch) {
      return false; // No leak summary found
    }

    const leakSummary = leakSummaryMatch[1];

    // Extract numbers for definitely lost, indirectly lost, and possibly lost
    const definitelyLostMatch = leakSummary.match(
      /definitely lost:\s*(\d+)\s*bytes/,
    );
    const indirectlyLostMatch = leakSummary.match(
      /indirectly lost:\s*(\d+)\s*bytes/,
    );
    const possiblyLostMatch = leakSummary.match(
      /possibly lost:\s*(\d+)\s*bytes/,
    );

    const definitelyLost = definitelyLostMatch
      ? parseInt(definitelyLostMatch[1])
      : 0;
    const indirectlyLost = indirectlyLostMatch
      ? parseInt(indirectlyLostMatch[1])
      : 0;
    const possiblyLost = possiblyLostMatch ? parseInt(possiblyLostMatch[1]) : 0;

    // Only consider it a memory leak if any of these are > 0
    return definitelyLost > 0 || indirectlyLost > 0 || possiblyLost > 0;
  }

  private validateOutput(
    actualOutput: string,
    testCase: TestCase,
  ): {
    passed: boolean;
    details: string[];
  } {
    const details: string[] = [];
    let passed = true;

    // Check expectedOutputContains
    if (testCase.expectedOutputContains) {
      for (const expectedString of testCase.expectedOutputContains) {
        if (actualOutput.includes(expectedString)) {
          details.push(`✅ Contains: "${expectedString}"`);
        } else {
          details.push(`❌ Missing: "${expectedString}"`);
          passed = false;
        }
      }
    }

    // Check expectedOutputExact
    if (testCase.expectedOutputExact) {
      const trimmedActual = actualOutput.trim();
      const trimmedExpected = testCase.expectedOutputExact.trim();
      if (trimmedActual === trimmedExpected) {
        details.push(`✅ Exact match: "${trimmedExpected}"`);
      } else {
        details.push(`❌ Expected exact: "${trimmedExpected}"`);
        details.push(`❌ But got: "${trimmedActual}"`);
        passed = false;
      }
    }

    // Check expectedOutput (each string should be present)
    if (testCase.expectedOutput) {
      for (const expectedString of testCase.expectedOutput) {
        if (actualOutput.includes(expectedString)) {
          details.push(`✅ Found: "${expectedString}"`);
        } else {
          details.push(`❌ Missing: "${expectedString}"`);
          passed = false;
        }
      }
    }

    // Check shouldNotContain
    if (testCase.shouldNotContain) {
      for (const forbiddenString of testCase.shouldNotContain) {
        if (!actualOutput.includes(forbiddenString)) {
          details.push(`✅ Correctly absent: "${forbiddenString}"`);
        } else {
          details.push(`❌ Should not contain: "${forbiddenString}"`);
          passed = false;
        }
      }
    }

    // If no output validation rules are specified, consider it passed
    if (
      !testCase.expectedOutput &&
      !testCase.expectedOutputContains &&
      !testCase.expectedOutputExact &&
      !testCase.shouldNotContain
    ) {
      details.push("ℹ️  No output validation rules specified");
    }

    return { passed, details };
  }

  private extractProgramOutput(stdoutText: string): string {
    // Simply remove ANSI escape codes and return the entire stdout
    return stdoutText
      .replace(/\x1b\[[0-9;]*m/g, "")
      .replace(/\x01|\x02/g, "")
      .trim();
  }

  private getTestCases(): TestCase[] {
    return [
      // Basic command tests
      {
        name: "simple_echo",
        command: "echo hello world",
        expectedExitCode: 0,
        description: "Test basic echo command",
        expectedOutputContains: ["hello world"],
      },
      {
        name: "echo_with_newline",
        command: "echo -n hello world",
        expectedExitCode: 0,
        description: "Test echo with -n flag",
        expectedOutputContains: ["hello world"],
      },
      {
        name: "echo_multiple_n_flags",
        command: "echo -nnn hello world",
        expectedExitCode: 0,
        description: "Test echo with multiple -n flags",
        expectedOutputContains: ["hello world"],
      },
      {
        name: "echo_invalid_flag",
        command: "echo -x hello world",
        expectedExitCode: 0,
        description: "Test echo with invalid flag (should print -x)",
        expectedOutputContains: ["-x hello world"],
      },
      {
        name: "echo_empty",
        command: "echo",
        expectedExitCode: 0,
        description: "Test echo with no arguments",
        expectedOutputExact: "",
      },

      // PWD tests
      {
        name: "pwd_basic",
        command: "pwd",
        expectedExitCode: 0,
        description: "Test pwd command",
        expectedOutputContains: ["/home/creid/Documents/42/minishell"],
      },

      // ENV tests
      {
        name: "env_basic",
        command: "env",
        expectedExitCode: 0,
        description: "Test env command",
        expectedOutputContains: ["PATH=", "HOME="],
      },

      // CD tests
      {
        name: "cd_home",
        command: "cd",
        expectedExitCode: 0,
        description: "Test cd to home directory",
      },
      {
        name: "cd_root",
        command: "cd /",
        expectedExitCode: 0,
        description: "Test cd to root directory",
      },
      {
        name: "cd_invalid",
        command: "cd /nonexistent/directory",
        expectedExitCode: 1,
        description: "Test cd to non-existent directory",
        expectedOutputContains: ["no such file or directory"],
      },

      // EXPORT tests
      {
        name: "export_basic",
        command: "export TEST_VAR=hello",
        expectedExitCode: 0,
        description: "Test basic export command",
      },
      {
        name: "export_display",
        command: "export",
        expectedExitCode: 0,
        description: "Test export without arguments",
        expectedOutputContains: ["PATH="],
      },
      {
        name: "export_multiple",
        command: "export VAR1=value1 VAR2=value2",
        expectedExitCode: 0,
        description: "Test export with multiple variables",
      },
      {
        name: "export_invalid_name",
        command: "export 123INVALID=value",
        expectedExitCode: 1,
        description: "Test export with invalid variable name",
        expectedOutputContains: ["not a valid identifier"],
      },

      // UNSET tests
      {
        name: "unset_basic",
        command: "unset PATH",
        expectedExitCode: 0,
        description: "Test basic unset command",
      },
      {
        name: "unset_multiple",
        command: "unset VAR1 VAR2",
        expectedExitCode: 0,
        description: "Test unset with multiple variables",
      },
      {
        name: "unset_nonexistent",
        command: "unset NONEXISTENT_VAR",
        expectedExitCode: 0,
        description: "Test unset with non-existent variable",
      },

      // Variable expansion tests
      {
        name: "variable_expansion_basic",
        command: "echo $USER",
        expectedExitCode: 0,
        description: "Test basic variable expansion",
        expectedOutputContains: [Deno.env.get("USER") || ""],
      },
      {
        name: "variable_expansion_path",
        command: "echo $PATH",
        expectedExitCode: 0,
        description: "Test PATH variable expansion",
        expectedOutputContains: ["/usr/bin"],
      },
      {
        name: "variable_expansion_nonexistent",
        command: "echo $NONEXISTENT_VAR",
        expectedExitCode: 0,
        description: "Test expansion of non-existent variable",
        expectedOutputExact: "",
      },
      {
        name: "variable_expansion_exit_status",
        command: "echo $?",
        expectedExitCode: 0,
        description: "Test exit status variable expansion",
        expectedOutputContains: ["0"],
      },

      // Pipe tests
      {
        name: "pipe_basic",
        command: "echo hello | cat",
        expectedExitCode: 0,
        description: "Test basic pipe",
        expectedOutputContains: ["hello"],
      },
      {
        name: "pipe_multiple",
        command: "echo hello world | cat | cat",
        expectedExitCode: 0,
        description: "Test multiple pipes",
        expectedOutputContains: ["hello world"],
      },
      {
        name: "pipe_with_builtin",
        command: "env | grep PATH",
        expectedExitCode: 0,
        description: "Test pipe with builtin command",
      },

      // Redirection tests
      {
        name: "redirect_output",
        command: "echo hello > /tmp/minishell_test.txt",
        expectedExitCode: 0,
        description: "Test output redirection",
      },
      {
        name: "redirect_append",
        command: "echo world >> /tmp/minishell_test.txt",
        expectedExitCode: 0,
        description: "Test append redirection",
      },
      {
        name: "redirect_input",
        command: "cat < /tmp/minishell_test.txt",
        expectedExitCode: 0,
        description: "Test input redirection",
      },

      // Complex command tests
      {
        name: "complex_pipe_redirect",
        command: "echo test | cat > /tmp/minishell_complex.txt",
        expectedExitCode: 0,
        description: "Test complex pipe and redirect",
      },
      {
        name: "multiple_commands_with_variables",
        command: "export TEST=value; echo $TEST",
        expectedExitCode: 0,
        description: "Test multiple commands with variables",
      },

      // Error handling tests
      {
        name: "command_not_found",
        command: "nonexistent_command",
        expectedExitCode: 127,
        description: "Test command not found error",
        expectedOutputContains: ["command not found"],
      },
      {
        name: "invalid_syntax_pipe",
        command: "echo hello |",
        expectedExitCode: 2,
        description: "Test invalid pipe syntax",
        expectedOutputContains: ["Parsing error"],
      },
      {
        name: "invalid_syntax_redirect",
        command: "echo hello >",
        expectedExitCode: 2,
        description: "Test invalid redirect syntax",
        expectedOutputContains: ["Parsing error"],
      },

      // Stress tests
      {
        name: "long_command_line",
        command: "echo " + "a".repeat(1000),
        expectedExitCode: 0,
        description: "Test very long command line",
      },
      {
        name: "many_arguments",
        command:
          "echo " + Array.from({ length: 100 }, (_, i) => `arg${i}`).join(" "),
        expectedExitCode: 0,
        description: "Test command with many arguments",
      },

      // Quoting tests
      {
        name: "single_quotes",
        command: "echo 'hello world'",
        expectedExitCode: 0,
        description: "Test single quotes",
      },
      {
        name: "double_quotes",
        command: 'echo "hello world"',
        expectedExitCode: 0,
        description: "Test double quotes",
      },
      {
        name: "mixed_quotes",
        command: `echo "hello 'world'"`,
        expectedExitCode: 0,
        description: "Test mixed quotes",
      },
      {
        name: "quotes_with_variables",
        command: `echo "User: $USER"`,
        expectedExitCode: 0,
        description: "Test quotes with variable expansion",
      },

      // Special characters
      {
        name: "semicolon_commands",
        command: "echo hello; echo world",
        expectedExitCode: 0,
        description: "Test semicolon separated commands",
      },
      {
        name: "ampersand_background",
        command: "echo hello &",
        expectedExitCode: 0,
        description: "Test background execution",
      },

      // Built-in edge cases
      {
        name: "cd_dash",
        command: "cd \\n cd -",
        expectedExitCode: 0,
        description: "Test cd with dash (previous directory)",
      },
      {
        name: "export_equals_only",
        command: "export =value",
        expectedExitCode: 1,
        description: "Test export with equals only",
      },
      {
        name: "export_no_value",
        command: "export NOVALUE",
        expectedExitCode: 0,
        description: "Test export without value",
      },

      // Memory stress tests
      {
        name: "memory_stress_large_env",
        command: Array.from(
          { length: 50 },
          (_, i) => `export VAR${i}=value${i}`,
        ).join("; "),
        expectedExitCode: 0,
        description: "Test memory handling with large environment",
      },
      {
        name: "memory_stress_deep_pipes",
        command: Array.from({ length: 10 }, () => "cat").join(" | "),
        expectedExitCode: 0,
        description: "Test memory handling with deep pipe chain",
      },

      // Exit tests (should be last)
      {
        name: "exit_success",
        command: "exit 0",
        expectedExitCode: 0,
        description: "Test exit with success code",
      },
      {
        name: "exit_failure",
        command: "exit 1",
        expectedExitCode: 1,
        description: "Test exit with failure code",
      },
      {
        name: "exit_no_argument",
        command: "exit",
        expectedExitCode: 0,
        description: "Test exit without argument",
      },
    ];
  }

  private async runSingleTest(testCase: TestCase): Promise<TestResult> {
    const fullCommand = `printf "${testCase.command}\\nexit \\\$?\\n" | valgrind --suppressions=${this.suppressionsPath} --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42 ${this.minishellPath}`;

    console.log(`🔍 Testing: ${testCase.name}`);
    if (testCase.description) {
      console.log(`   Description: ${testCase.description}`);
    }
    console.log(`   Command: ${testCase.command}`);

    try {
      const process = new Deno.Command("sh", {
        args: ["-c", fullCommand],
        stdout: "piped",
        stderr: "piped",
      });

      const { code, stdout, stderr } = await process.output();

      const stdoutText = new TextDecoder().decode(stdout);
      const stderrText = new TextDecoder().decode(stderr);
      const valgrindOutput = stderrText;

      // Extract actual program output from Valgrind output
      // Valgrind writes to stderr, so program output is in stdout
      // But we need to filter out the shell prompt and other shell-specific output
      const actualOutput = this.extractProgramOutput(stdoutText);

      // Validate output
      const outputValidation = this.validateOutput(actualOutput, testCase);

      // Check for memory leaks in Valgrind output
      // We need to parse the actual numbers, not just check if the strings exist
      const hasMemoryLeaks =
        this.parseMemoryLeaks(valgrindOutput) || code === 42;

      // Determine if test passed
      const expectedCode = testCase.expectedExitCode ?? 0;
      const exitCodeMatch = code === expectedCode;
      const memoryLeaksOk = testCase.expectMemoryLeaks
        ? hasMemoryLeaks
        : !hasMemoryLeaks;
      const passed = exitCodeMatch && memoryLeaksOk && outputValidation.passed;

      // Collect failure reasons
      const failureReasons: string[] = [];
      if (!exitCodeMatch) {
        failureReasons.push(
          `Exit code mismatch: expected ${expectedCode}, got ${code}`,
        );
      }
      if (!memoryLeaksOk) {
        if (testCase.expectMemoryLeaks) {
          failureReasons.push("Expected memory leaks but none found");
        } else {
          failureReasons.push("Memory leaks detected");
          // Add leak details
          const leakSummaryMatch = valgrindOutput.match(
            /LEAK SUMMARY:(.*?)(?=\n==|\n\n|$)/s,
          );
          if (leakSummaryMatch) {
            failureReasons.push(`Leak details: ${leakSummaryMatch[1].trim()}`);
          }
        }
      }
      if (!outputValidation.passed) {
        failureReasons.push("Output validation failed");
        failureReasons.push(
          ...outputValidation.details.filter((d) => d.startsWith("❌")),
        );
      }

      const result: TestResult = {
        name: testCase.name,
        passed,
        exitCode: code,
        hasMemoryLeaks,
        valgrindOutput,
        actualOutput,
        outputValidation,
        failureReasons,
      };

      if (passed) {
        console.log(`   ✅ PASSED`);
        // Show output validation details for passed tests if they exist
        if (outputValidation.details.length > 0) {
          console.log(
            `      Output validation: ${outputValidation.details.join(", ")}`,
          );
        }
        this.passedTests++;
      } else {
        console.log(`   ❌ FAILED`);
        if (!exitCodeMatch) {
          console.log(
            `      Expected exit code: ${expectedCode}, got: ${code}`,
          );
        }
        if (!memoryLeaksOk) {
          if (testCase.expectMemoryLeaks) {
            console.log(`      Expected memory leaks but none found`);
          } else {
            console.log(`      Memory leaks detected!`);
            // Show more details about the memory leaks
            const leakSummaryMatch = valgrindOutput.match(
              /LEAK SUMMARY:(.*?)(?=\n==|\n\n|$)/s,
            );
            if (leakSummaryMatch) {
              console.log(`      Leak details: ${leakSummaryMatch[1].trim()}`);
            }
          }
        }
        if (!outputValidation.passed) {
          console.log(`      Output validation failed:`);
          for (const detail of outputValidation.details) {
            console.log(`        ${detail}`);
          }
          if (actualOutput) {
            console.log(`      Actual output: "${actualOutput}"`);
          }
        }
        this.failedTests++;
      }

      console.log(); // Empty line for readability

      return result;
    } catch (error) {
      console.log(`   ❌ ERROR: ${error.message}`);
      this.failedTests++;
      return {
        name: testCase.name,
        passed: false,
        exitCode: -1,
        hasMemoryLeaks: false,
        valgrindOutput: "",
        actualOutput: "",
        outputValidation: {
          passed: false,
          details: [`❌ Test execution failed: ${error.message}`],
        },
        failureReasons: [`Test execution failed: ${error.message}`],
        error: error.message,
      };
    }
  }

  private async runAllTests(): Promise<void> {
    const testCases = this.getTestCases();

    console.log(`📋 Running ${testCases.length} tests...\n`);

    for (const testCase of testCases) {
      const result = await this.runSingleTest(testCase);
      this.testResults.push(result);
    }
  }

  private async generateReport(): Promise<void> {
    const totalTests = this.testResults.length;
    const successRate = ((this.passedTests / totalTests) * 100).toFixed(1);

    console.log("=".repeat(60));
    console.log("📊 TEST RESULTS SUMMARY");
    console.log("=".repeat(60));
    console.log(`Total tests: ${totalTests}`);
    console.log(`Passed: ${this.passedTests}`);
    console.log(`Failed: ${this.failedTests}`);
    console.log(`Success rate: ${successRate}%`);
    console.log();

    // Show failed tests details
    if (this.failedTests > 0) {
      console.log("❌ FAILED TESTS:");
      console.log("-".repeat(40));

      for (const result of this.testResults) {
        if (!result.passed) {
          console.log(`• ${result.name}`);
          console.log(`  Exit code: ${result.exitCode}`);
          console.log(
            `  Memory leaks: ${result.hasMemoryLeaks ? "YES" : "NO"}`,
          );
          if (result.failureReasons.length > 0) {
            console.log(`  Failure reasons:`);
            for (const reason of result.failureReasons) {
              console.log(`    - ${reason}`);
            }
          }
          if (result.error) {
            console.log(`  Error: ${result.error}`);
          }
          if (result.actualOutput) {
            console.log(`  Actual output: "${result.actualOutput}"`);
          }
          console.log();
        }
      }
    }

    // Generate detailed report file
    const reportPath = join("tools", "test_report.json");
    const reportData = {
      timestamp: new Date().toISOString(),
      summary: {
        totalTests,
        passedTests: this.passedTests,
        failedTests: this.failedTests,
        successRate: parseFloat(successRate),
      },
      results: this.testResults,
    };

    await Deno.writeTextFile(reportPath, JSON.stringify(reportData, null, 2));
    console.log(`📄 Detailed report saved to: ${reportPath}`);

    // Also generate a simple HTML report
    await this.generateHtmlReport(reportData);
  }

  private async generateHtmlReport(reportData: any): Promise<void> {
    const htmlContent = `
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Minishell Test Report</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; }
        .header { background: #f0f0f0; padding: 20px; border-radius: 5px; }
        .summary { display: flex; gap: 20px; margin: 20px 0; }
        .metric { padding: 10px; border-radius: 5px; text-align: center; }
        .passed { background: #d4edda; color: #155724; }
        .failed { background: #f8d7da; color: #721c24; }
        .total { background: #cce5ff; color: #004085; }
        .test-result { margin: 10px 0; padding: 10px; border-radius: 5px; }
        .test-passed { background: #d4edda; }
        .test-failed { background: #f8d7da; }
        .details { margin-top: 10px; font-size: 12px; color: #666; }
        pre { background: #f8f9fa; padding: 10px; border-radius: 3px; overflow-x: auto; }
    </style>
</head>
<body>
    <div class="header">
        <h1>🐚 Minishell Test Report</h1>
        <p>Generated on: ${new Date(reportData.timestamp).toLocaleString()}</p>
    </div>

    <div class="summary">
        <div class="metric total">
            <h3>${reportData.summary.totalTests}</h3>
            <p>Total Tests</p>
        </div>
        <div class="metric passed">
            <h3>${reportData.summary.passedTests}</h3>
            <p>Passed</p>
        </div>
        <div class="metric failed">
            <h3>${reportData.summary.failedTests}</h3>
            <p>Failed</p>
        </div>
        <div class="metric">
            <h3>${reportData.summary.successRate}%</h3>
            <p>Success Rate</p>
        </div>
    </div>

    <h2>Test Results</h2>
    ${reportData.results
      .map(
        (result: TestResult) => `
        <div class="test-result ${result.passed ? "test-passed" : "test-failed"}">
            <h4>${result.passed ? "✅" : "❌"} ${result.name}</h4>
            <div class="details">
                <p><strong>Exit Code:</strong> ${result.exitCode}</p>
                <p><strong>Memory Leaks:</strong> ${result.hasMemoryLeaks ? "YES" : "NO"}</p>
                ${result.error ? `<p><strong>Error:</strong> ${result.error}</p>` : ""}
                ${
                  result.failureReasons && result.failureReasons.length > 0
                    ? `
                    <div>
                        <strong>Failure Reasons:</strong>
                        <ul>
                            ${result.failureReasons.map((reason) => `<li>${reason}</li>`).join("")}
                        </ul>
                    </div>
                `
                    : ""
                }
                ${
                  result.actualOutput
                    ? `
                    <details>
                        <summary>Actual Output</summary>
                        <pre>${result.actualOutput}</pre>
                    </details>
                `
                    : ""
                }
                ${
                  result.valgrindOutput
                    ? `
                    <details>
                        <summary>Valgrind Output</summary>
                        <pre>${result.valgrindOutput}</pre>
                    </details>
                `
                    : ""
                }
            </div>
        </div>
    `,
      )
      .join("")}

</body>
</html>
        `;

    const htmlPath = join("tools", "test_report.html");
    await Deno.writeTextFile(htmlPath, htmlContent);
    console.log(`🌐 HTML report saved to: ${htmlPath}`);
  }

  async run(): Promise<void> {
    if (!(await this.init())) {
      Deno.exit(1);
    }

    // Clean up any existing test files
    try {
      await Deno.remove("/tmp/minishell_test.txt");
    } catch {
      // File doesn't exist, that's fine
    }
    try {
      await Deno.remove("/tmp/minishell_complex.txt");
    } catch {
      // File doesn't exist, that's fine
    }

    await this.runAllTests();
    await this.generateReport();

    // Exit with appropriate code
    if (this.failedTests > 0) {
      console.log(`\n❌ Some tests failed. Exiting with code 1.`);
      Deno.exit(1);
    } else {
      console.log(`\n✅ All tests passed! 🎉`);
      Deno.exit(0);
    }
  }
}

// Main execution
if (import.meta.main) {
  const tester = new MinishellTester();
  await tester.run();
}
