#!/bin/bash

echo "=== Advanced Multi-Base Arithmetic Engine Test Suite (Pure C) ==="
echo "Testing various bases and edge cases with NO classes, NO STL, NO vectors..."
echo ""

# Test 1: Binary arithmetic
echo "Test 1: Binary (Base 2) - Large numbers"
echo "2
1111111111
1010101010" | ./advanced_arithmetic_engine
echo ""

# Test 2: Hexadecimal arithmetic
echo "Test 2: Hexadecimal (Base 16) - Color values"
echo "16
FF0000
00FF00" | ./advanced_arithmetic_engine
echo ""

# Test 3: Octal arithmetic
echo "Test 3: Octal (Base 8) - Unix permissions"
echo "8
7777777777
1234567" | ./advanced_arithmetic_engine
echo ""

# Test 4: Decimal arithmetic with maximum 10-digit numbers
echo "Test 4: Decimal (Base 10) - Maximum range"
echo "10
9999999999
1234567890" | ./advanced_arithmetic_engine
echo ""

# Test 5: Ternary arithmetic
echo "Test 5: Ternary (Base 3) - Balanced ternary"
echo "3
2222222222
1111111111" | ./advanced_arithmetic_engine
echo ""

# Test 6: Duodecimal arithmetic
echo "Test 6: Duodecimal (Base 12) - Time/angle systems"
echo "12
BBBBBBBBBB
AAAAAAAAAA" | ./advanced_arithmetic_engine
echo ""

# Test 7: Edge case - Single digit operations
echo "Test 7: Single digit operations in base 16"
echo "16
F
A" | ./advanced_arithmetic_engine
echo ""

# Test 8: Edge case - Zero operations
echo "Test 8: Zero operations in base 10"
echo "10
1234567890
0" | ./advanced_arithmetic_engine
echo ""

# Test 9: Edge case - Identity operations
echo "Test 9: Identity operations in base 8"
echo "8
1234567
1" | ./advanced_arithmetic_engine
echo ""

# Test 10: Maximum binary number
echo "Test 10: Maximum binary number (10 digits)"
echo "2
1111111111
1" | ./advanced_arithmetic_engine
echo ""

# Test 11: Edge case - Maximum hexadecimal
echo "Test 11: Maximum hexadecimal number (10 digits)"
echo "16
FFFFFFFFF
1" | ./advanced_arithmetic_engine
echo ""

# Test 12: Edge case - Division by zero
echo "Test 12: Division by zero error handling"
echo "10
1234567890
0" | ./advanced_arithmetic_engine
echo ""

# Test 13: Quinary arithmetic
echo "Test 13: Quinary (Base 5) - Finger counting"
echo "5
4444444444
1234" | ./advanced_arithmetic_engine
echo ""

# Test 14: Septenary arithmetic
echo "Test 14: Septenary (Base 7) - Week-based systems"
echo "7
6666666666
123456" | ./advanced_arithmetic_engine
echo ""

echo "=== All tests completed ==="
echo "Implementation uses ONLY:"
echo "- Basic C functions"
echo "- Arrays (no vectors/containers)"
echo "- Recursion (no loops)"
echo "- Fundamental data types"
echo "- No classes, no STL, no C++ features"