#!/bin/bash

# Wrapper script to run the Deno test suite
# This script ensures the minishell is built before running tests

set -e

echo "🔧 Building minishell..."
make

echo "🧪 Running test suite..."
deno run --allow-run --allow-read --allow-write tools/tests.ts

echo "✅ Test suite completed!"
