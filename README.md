# Advanced Multi-Base Arithmetic Engine

A sophisticated arithmetic engine capable of performing mathematical operations on numbers up to 10 digits long across multiple numeral systems (bases 2-16) without using string data types or loops.

## Features

- **Multi-Base Support**: Handles bases 2 through 16 (binary, ternary, quaternary, quinary, senary, septenary, octal, nonary, decimal, undecimal, duodecimal, tridecimal, tetradecimal, pentadecimal, and hexadecimal)
- **Large Number Support**: Processes numbers up to 10 digits in any supported base
- **Four Arithmetic Operations**: Addition, subtraction, multiplication, and division
- **No String Operations**: Uses only numeric data types and algorithmic techniques
- **No Loops**: Implements all operations using recursive algorithms
- **Precision Guaranteed**: Handles the full 10-digit range with mathematical exactitude

## Technical Implementation

### Key Algorithms

1. **Base Conversion**: Recursive algorithms for converting between any base and decimal
2. **Addition**: Digit-by-digit addition with carry propagation using recursion
3. **Subtraction**: Digit-by-digit subtraction with borrow handling using recursion
4. **Multiplication**: Recursive multiplication using distributive property and digit-by-digit operations
5. **Division**: Long division algorithm with quotient and remainder calculation

### Data Structures

- Uses `std::vector<int>` to represent multi-digit numbers
- Each element represents a single digit in the specified base
- Maximum of 10 digits supported per number

### Constraints Met

- ✅ No string data types or string library functions
- ✅ No loops (for, while, do-while)
- ✅ Works with actual numeric types
- ✅ Handles up to 10-digit numbers
- ✅ Supports bases 2-16
- ✅ All four arithmetic operations implemented
- ✅ Results returned in the same base as input

## Usage

### Compilation

```bash
g++ -o advanced_arithmetic_engine advanced_arithmetic_engine.cpp -std=c++17
```

### Running the Program

```bash
./advanced_arithmetic_engine
```

The program will prompt you for:
1. The numeral system base (2-16)
2. First number in the specified base
3. Second number in the specified base

### Example Session

```
=== Advanced Multi-Base Arithmetic Engine ===
Supports bases 2-16 with up to 10-digit numbers
=============================================
Enter the numeral system base (2-16): 16
Enter first number (base 16): FF
Enter second number (base 16): A

=== Results (Base 16) ===
Addition: FF + A = 109
Subtraction: FF - A = F5
Multiplication: FF * A = 9F6
Division: FF / A = 19 (remainder: 5)
```

## Test Suite

Run the comprehensive test suite:

```bash
./test_arithmetic_engine.sh
```

This tests various bases, edge cases, and maximum number ranges.

## Supported Numeral Systems

| Base | Name | Digits Used | Common Uses |
|------|------|-------------|-------------|
| 2 | Binary | 0-1 | Digital logic, computer science |
| 3 | Ternary | 0-2 | Balanced ternary systems |
| 4 | Quaternary | 0-3 | DNA sequences, some counting systems |
| 5 | Quinary | 0-4 | Finger counting |
| 6 | Senary | 0-5 | Some ancient counting systems |
| 7 | Septenary | 0-6 | Week-based systems |
| 8 | Octal | 0-7 | Unix file permissions |
| 9 | Nonary | 0-8 | Some mathematical applications |
| 10 | Decimal | 0-9 | Standard human counting |
| 11 | Undecimal | 0-A | Specialized applications |
| 12 | Duodecimal | 0-B | Time, angles, dozen-based systems |
| 13 | Tridecimal | 0-C | Specialized applications |
| 14 | Tetradecimal | 0-D | Specialized applications |
| 15 | Pentadecimal | 0-E | Specialized applications |
| 16 | Hexadecimal | 0-F | Memory addresses, color codes |

## Error Handling

The system includes comprehensive error handling for:
- Invalid base selection (outside 2-16 range)
- Invalid digits for the specified base
- Numbers exceeding 10-digit limit
- Division by zero
- Negative results in subtraction

## Performance Characteristics

- **Time Complexity**: O(n) for addition/subtraction, O(n²) for multiplication, O(n²) for division
- **Space Complexity**: O(n) where n is the number of digits
- **Memory Usage**: Minimal - only stores digit arrays and temporary variables
- **Precision**: Exact arithmetic with no floating-point errors

## Applications

This arithmetic engine is suitable for:
- Cryptographic systems requiring precise large number arithmetic
- Scientific calculators with multi-base support
- Educational tools for understanding different numeral systems
- Systems programming where base conversion is critical
- Mathematical research involving non-decimal bases

## Technical Notes

- All operations are implemented using recursive algorithms to avoid loops
- The system uses C++ `long long` for intermediate decimal calculations
- Digit arrays are processed from right to left (least significant to most significant)
- Carry and borrow propagation is handled recursively
- Results are automatically formatted in the same base as the input