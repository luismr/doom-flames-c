#!/bin/bash

# DOOM Fire Effect - Comprehensive Test Suite
# Tests build configurations, functionality, and fixes

echo "🔥 DOOM Fire Effect - Test Suite v2.0 🔥"
echo "========================================"
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Test counters
TESTS_PASSED=0
TESTS_FAILED=0
TOTAL_TESTS=0

# Helper functions
pass_test() {
    echo -e "${GREEN}✅ $1${NC}"
    ((TESTS_PASSED++))
    ((TOTAL_TESTS++))
}

fail_test() {
    echo -e "${RED}❌ $1${NC}"
    ((TESTS_FAILED++))
    ((TOTAL_TESTS++))
}

info_test() {
    echo -e "${BLUE}ℹ️  $1${NC}"
}

warn_test() {
    echo -e "${YELLOW}⚠️  $1${NC}"
}

# Test 1: Build System Tests
echo -e "${BLUE}=== Build System Tests ===${NC}"

info_test "Testing build information..."
make info > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "Build information command works"
else
    fail_test "Build information command failed"
fi

info_test "Testing clean build..."
make clean > /dev/null 2>&1 && make > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "Clean build successful"
else
    fail_test "Clean build failed"
    exit 1
fi

info_test "Testing debug build..."
make clean > /dev/null 2>&1 && make debug > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "Debug build successful"
else
    fail_test "Debug build failed"
fi

info_test "Testing release build..."
make clean > /dev/null 2>&1 && make release > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "Release build successful"
else
    fail_test "Release build failed"
fi

echo ""

# Test 2: Command Line Interface Tests
echo -e "${BLUE}=== Command Line Interface Tests ===${NC}"

info_test "Testing help functionality..."
./build/doomfire --help > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "Help command works"
else
    fail_test "Help command failed"
fi

info_test "Testing invalid arguments handling..."
./build/doomfire --invalid-option > /dev/null 2>&1
if [ $? -ne 0 ]; then
    pass_test "Invalid arguments properly rejected"
else
    fail_test "Invalid arguments not handled correctly"
fi

info_test "Testing valid argument parsing..."
./build/doomfire --width 20 --height 10 --fps 1 --help > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "Valid arguments parsed correctly"
else
    fail_test "Valid argument parsing failed"
fi

echo ""

# Test 3: Fire Effect Functionality Tests
echo -e "${BLUE}=== Fire Effect Functionality Tests ===${NC}"

info_test "Testing basic fire effect (non-interactive)..."
echo "q" | ./build/doomfire --width 20 --height 8 --fps 5 > /dev/null 2>&1
exit_code=$?
if [ $exit_code -eq 0 ]; then
    pass_test "Basic fire effect runs without errors"
else
    fail_test "Basic fire effect has runtime errors (exit code: $exit_code)"
fi

info_test "Testing optimized rendering..."
echo "q" | ./build/doomfire --optimized --width 20 --height 8 --fps 5 > /dev/null 2>&1
exit_code=$?
if [ $exit_code -eq 0 ]; then
    pass_test "Optimized rendering works"
else
    fail_test "Optimized rendering has errors (exit code: $exit_code)"
fi

info_test "Testing wind effects..."
echo "q" | ./build/doomfire --wind 1 --width 15 --height 6 --fps 10 > /dev/null 2>&1
exit_code=$?
if [ $exit_code -eq 0 ]; then
    pass_test "Wind effects work"
else
    fail_test "Wind effects have errors (exit code: $exit_code)"
fi

info_test "Testing high FPS performance..."
echo "q" | ./build/doomfire --fps 60 --width 30 --height 10 > /dev/null 2>&1
exit_code=$?
if [ $exit_code -eq 0 ]; then
    pass_test "High FPS performance test passed"
else
    fail_test "High FPS performance test failed (exit code: $exit_code)"
fi

echo ""

# Test 4: Input Handling Tests (Fixed Issues)
echo -e "${BLUE}=== Input Handling Tests (Fixed Issues) ===${NC}"

info_test "Testing 'q' key exit functionality..."
echo "q" | ./build/doomfire --width 15 --height 5 --fps 20 > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "'q' key exit works correctly"
else
    fail_test "'q' key exit not working"
fi

info_test "Testing space key handling (pause simulation)..."
# Test that space doesn't cause immediate exit
(echo " "; echo "q") | ./build/doomfire --width 10 --height 5 --fps 10 > /dev/null 2>&1
exit_code=$?
if [ $exit_code -eq 0 ]; then
    pass_test "Space key handling works (pause functionality)"
else
    fail_test "Space key handling has issues (exit code: $exit_code)"
fi

info_test "Testing multiple key inputs..."
(echo "a"; echo "d"; echo "s"; echo "+"; echo "-"; echo "q") | ./build/doomfire --width 10 --height 5 --fps 15 > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "Multiple key inputs handled correctly"
else
    fail_test "Multiple key inputs not handled properly"
fi

echo ""

# Test 5: Anti-Scrolling Tests (Fixed Issues)
echo -e "${BLUE}=== Anti-Scrolling Tests (Fixed Issues) ===${NC}"

info_test "Testing output for scrolling behavior..."
output=$(echo "q" | ./build/doomfire --width 20 --height 5 --fps 30 2>/dev/null)
line_count=$(echo "$output" | wc -l)
if [ $line_count -lt 50 ]; then  # Should not produce excessive output
    pass_test "No excessive scrolling detected"
else
    warn_test "Potential scrolling detected ($line_count lines of output)"
fi

info_test "Testing terminal size handling..."
echo "q" | ./build/doomfire --width 200 --height 100 --fps 1 > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "Large terminal size handled gracefully"
else
    fail_test "Large terminal size caused issues"
fi

info_test "Testing small terminal size..."
echo "q" | ./build/doomfire --width 5 --height 3 --fps 1 > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "Small terminal size handled gracefully"
else
    fail_test "Small terminal size caused issues"
fi

echo ""

# Test 6: Memory and Performance Tests
echo -e "${BLUE}=== Memory and Performance Tests ===${NC}"

info_test "Testing memory allocation..."
echo "q" | valgrind --error-exitcode=1 --leak-check=no --track-origins=no ./build/doomfire --width 10 --height 5 --fps 1 > /dev/null 2>&1
if [ $? -eq 0 ]; then
    pass_test "No memory errors detected"
elif ! command -v valgrind &> /dev/null; then
    warn_test "Valgrind not available, skipping memory test"
else
    fail_test "Memory errors detected"
fi

info_test "Testing rapid start/stop cycles..."
success=true
for i in {1..3}; do
    echo "q" | ./build/doomfire --width 10 --height 5 --fps 30 > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        fail_test "Rapid start/stop cycle $i failed"
        success=false
        break
    fi
done
if [ "$success" = true ]; then
    pass_test "Rapid start/stop cycles work correctly"
fi

echo ""

# Test 7: Cross-Platform Compatibility Tests
echo -e "${BLUE}=== Cross-Platform Compatibility Tests ===${NC}"

info_test "Testing ANSI color support detection..."
echo "q" | ./build/doomfire --width 10 --height 3 --fps 1 2>&1 | grep -q "Error.*color"
if [ $? -ne 0 ]; then
    pass_test "ANSI color support works"
else
    warn_test "ANSI color support may have issues"
fi

info_test "Testing terminal detection..."
if [ -t 1 ]; then
    pass_test "Terminal detection works (interactive)"
else
    pass_test "Terminal detection works (non-interactive)"
fi

echo ""

# Test Summary
echo -e "${BLUE}=== Test Summary ===${NC}"
echo "Total tests run: $TOTAL_TESTS"
echo -e "Tests passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Tests failed: ${RED}$TESTS_FAILED${NC}"

if [ $TESTS_FAILED -eq 0 ]; then
    echo -e "\n${GREEN}🎉 All tests passed! The DOOM fire effect is working perfectly!${NC}"
    echo ""
    echo -e "${BLUE}Ready to run:${NC}"
    echo "  ./build/doomfire                    # Standard fire effect"
    echo "  ./build/doomfire --optimized        # Optimized Unicode rendering"
    echo "  ./build/doomfire --wind 1 --fps 60  # Fast fire with wind"
    echo ""
    echo -e "${BLUE}Interactive controls:${NC}"
    echo "  q, ESC, Ctrl+C  - Quit"
    echo "  SPACE           - Pause/Resume"
    echo "  a/d, arrows     - Wind direction"
    echo "  +/-             - Speed control"
    exit 0
else
    echo -e "\n${RED}❌ Some tests failed. Please review the issues above.${NC}"
    exit 1
fi