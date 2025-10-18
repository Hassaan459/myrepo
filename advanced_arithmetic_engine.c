#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGITS 10

// Global variables for base
int base;

// Function declarations
int getDigitValue(char digit);
char getDigitChar(int value);
long long toDecimalRecursive(int digits[], int start, int end);
long long toDecimal(int digits[], int length);
void fromDecimalRecursive(long long decimal, int result[], int* length);
void fromDecimal(long long decimal, int result[], int* length);
void addDigitsRecursive(int a[], int b[], int pos, int* carry, int result[], int* resultLen);
void addDigits(int a[], int aLen, int b[], int bLen, int result[], int* resultLen);
void subtractDigitsRecursive(int a[], int b[], int pos, int* borrow, int result[], int* resultLen);
void subtractDigits(int a[], int aLen, int b[], int bLen, int result[], int* resultLen);
void multiplyDigits(int a[], int aLen, int b[], int bLen, int result[], int* resultLen);
void divideDigits(int a[], int aLen, int b[], int bLen, int quotient[], int* quotientLen, int remainder[], int* remainderLen);
int compareDigitsRecursive(int a[], int b[], int pos, int len);
int compareDigits(int a[], int aLen, int b[], int bLen);
void parseNumber(const char* input, int digits[], int* length);
void toString(int digits[], int length, char* result);
void add(int a[], int aLen, int b[], int bLen, int result[], int* resultLen);
void subtract(int a[], int aLen, int b[], int bLen, int result[], int* resultLen);
void multiply(int a[], int aLen, int b[], int bLen, int result[], int* resultLen);
void divide(int a[], int aLen, int b[], int bLen, int quotient[], int* quotientLen, int remainder[], int* remainderLen);

// Helper function to get digit value from character
int getDigitValue(char digit) {
    if (digit >= '0' && digit <= '9') {
        return digit - '0';
    } else if (digit >= 'A' && digit <= 'F') {
        return digit - 'A' + 10;
    }
    return -1; // Invalid digit
}

// Helper function to get character from digit value
char getDigitChar(int value) {
    if (value >= 0 && value <= 9) {
        return '0' + value;
    } else if (value >= 10 && value <= 15) {
        return 'A' + value - 10;
    }
    return '?'; // Invalid value
}

long long toDecimalRecursive(int digits[], int start, int end) {
    if (start > end) return 0;
    if (start == end) return digits[start];
    
    int mid = start + (end - start) / 2;
    long long left = toDecimalRecursive(digits, start, mid);
    long long right = toDecimalRecursive(digits, mid + 1, end);
    
    // Combine results: left * base^(end-mid) + right
    long long power = 1;
    int i = 0;
    while (i < end - mid) {
        power *= base;
        i++;
    }
    
    return left * power + right;
}

// Convert multi-base number to decimal using recursive approach
long long toDecimal(int digits[], int length) {
    if (length == 0) return 0;
    if (length == 1) return digits[0];
    
    // Use recursive approach instead of loops
    return toDecimalRecursive(digits, 0, length - 1);
}

// Convert decimal to multi-base using recursive approach
void fromDecimal(long long decimal, int result[], int* length) {
    if (decimal == 0) {
        result[0] = 0;
        *length = 1;
        return;
    }
    
    *length = 0;
    fromDecimalRecursive(decimal, result, length);
}

void fromDecimalRecursive(long long decimal, int result[], int* length) {
    if (decimal == 0) return;
    
    fromDecimalRecursive(decimal / base, result, length);
    result[(*length)++] = decimal % base;
}

// Add two digit arrays
void addDigits(int a[], int aLen, int b[], int bLen, int result[], int* resultLen) {
    int carry = 0;
    int maxLen = (aLen > bLen) ? aLen : bLen;
    
    // Pad shorter number with zeros
    int paddedA[MAX_DIGITS];
    int paddedB[MAX_DIGITS];
    int paddedALen = maxLen;
    int paddedBLen = maxLen;
    
    // Pad a
    int aOffset = maxLen - aLen;
    int i = 0;
    while (i < aOffset) {
        paddedA[i] = 0;
        i++;
    }
    i = 0;
    while (i < aLen) {
        paddedA[i + aOffset] = a[i];
        i++;
    }
    
    // Pad b
    int bOffset = maxLen - bLen;
    i = 0;
    while (i < bOffset) {
        paddedB[i] = 0;
        i++;
    }
    i = 0;
    while (i < bLen) {
        paddedB[i + bOffset] = b[i];
        i++;
    }
    
    // Add digits from right to left using recursive approach
    *resultLen = 0;
    addDigitsRecursive(paddedA, paddedB, maxLen - 1, &carry, result, resultLen);
    
    if (carry > 0) {
        // Shift result right and add carry at beginning
        i = *resultLen;
        while (i > 0) {
            result[i] = result[i-1];
            i--;
        }
        result[0] = carry;
        (*resultLen)++;
    }
}

void addDigitsRecursive(int a[], int b[], int pos, int* carry, int result[], int* resultLen) {
    if (pos < 0) return;
    
    int sum = a[pos] + b[pos] + *carry;
    *carry = sum / base;
    int digit = sum % base;
    
    addDigitsRecursive(a, b, pos - 1, carry, result, resultLen);
    result[(*resultLen)++] = digit;
}

// Subtract two digit arrays (assumes a >= b)
void subtractDigits(int a[], int aLen, int b[], int bLen, int result[], int* resultLen) {
    int borrow = 0;
    int maxLen = (aLen > bLen) ? aLen : bLen;
    
    // Pad shorter number with zeros
    int paddedA[MAX_DIGITS];
    int paddedB[MAX_DIGITS];
    int paddedALen = maxLen;
    int paddedBLen = maxLen;
    
    // Pad a
    int aOffset = maxLen - aLen;
    int i = 0;
    while (i < aOffset) {
        paddedA[i] = 0;
        i++;
    }
    i = 0;
    while (i < aLen) {
        paddedA[i + aOffset] = a[i];
        i++;
    }
    
    // Pad b
    int bOffset = maxLen - bLen;
    i = 0;
    while (i < bOffset) {
        paddedB[i] = 0;
        i++;
    }
    i = 0;
    while (i < bLen) {
        paddedB[i + bOffset] = b[i];
        i++;
    }
    
    // Subtract digits from right to left using recursive approach
    *resultLen = 0;
    subtractDigitsRecursive(paddedA, paddedB, maxLen - 1, &borrow, result, resultLen);
    
    // Remove leading zeros
    while (*resultLen > 1 && result[0] == 0) {
        i = 0;
        while (i < *resultLen - 1) {
            result[i] = result[i + 1];
            i++;
        }
        (*resultLen)--;
    }
}

void subtractDigitsRecursive(int a[], int b[], int pos, int* borrow, int result[], int* resultLen) {
    if (pos < 0) return;
    
    int diff = a[pos] - b[pos] - *borrow;
    if (diff < 0) {
        diff += base;
        *borrow = 1;
    } else {
        *borrow = 0;
    }
    
    subtractDigitsRecursive(a, b, pos - 1, borrow, result, resultLen);
    result[(*resultLen)++] = diff;
}

// Multiply two digit arrays using digit-by-digit multiplication
void multiplyDigits(int a[], int aLen, int b[], int bLen, int result[], int* resultLen) {
    if (aLen == 0 || bLen == 0) {
        result[0] = 0;
        *resultLen = 1;
        return;
    }
    if (aLen == 1 && a[0] == 0) {
        result[0] = 0;
        *resultLen = 1;
        return;
    }
    if (bLen == 1 && b[0] == 0) {
        result[0] = 0;
        *resultLen = 1;
        return;
    }
    if (aLen == 1 && a[0] == 1) {
        int i = 0;
        while (i < bLen) {
            result[i] = b[i];
            i++;
        }
        *resultLen = bLen;
        return;
    }
    if (bLen == 1 && b[0] == 1) {
        int i = 0;
        while (i < aLen) {
            result[i] = a[i];
            i++;
        }
        *resultLen = aLen;
        return;
    }
    
    // Initialize result array with zeros
    int tempResult[MAX_DIGITS * 2];
    int i = 0;
    while (i < MAX_DIGITS * 2) {
        tempResult[i] = 0;
        i++;
    }
    
    // Handle case where one number is zero
    if ((aLen == 1 && a[0] == 0) || (bLen == 1 && b[0] == 0)) {
        result[0] = 0;
        *resultLen = 1;
        return;
    }
    
    // Multiply each digit of a with each digit of b
    i = aLen - 1;
    while (i >= 0) {
        int j = bLen - 1;
        while (j >= 0) {
            int product = a[i] * b[j];
            int pos1 = i + j;
            int pos2 = i + j + 1;
            
            // Bounds checking
            if (pos1 >= 0 && pos1 < MAX_DIGITS * 2 && pos2 >= 0 && pos2 < MAX_DIGITS * 2) {
                // Add product to tempResult
                product += tempResult[pos2];
                tempResult[pos2] = product % base;
                tempResult[pos1] += product / base;
                
                // Handle carry
                int carry = tempResult[pos1] / base;
                tempResult[pos1] %= base;
                int k = pos1 - 1;
                while (carry > 0 && k >= 0 && k < MAX_DIGITS * 2) {
                    tempResult[k] += carry;
                    carry = tempResult[k] / base;
                    tempResult[k] %= base;
                    k--;
                }
            }
            j--;
        }
        i--;
    }
    
    // Find the actual length of the result
    *resultLen = 0;
    i = 0;
    while (i < MAX_DIGITS * 2) {
        if (tempResult[i] != 0 || *resultLen > 0) {
            result[*resultLen] = tempResult[i];
            (*resultLen)++;
        }
        i++;
    }
    
    if (*resultLen == 0) {
        result[0] = 0;
        *resultLen = 1;
    }
}

// Divide two digit arrays using recursive approach
void divideDigits(int a[], int aLen, int b[], int bLen, int quotient[], int* quotientLen, int remainder[], int* remainderLen) {
    if (bLen == 0 || (bLen == 1 && b[0] == 0)) {
        printf("Division Error: Division by zero\n");
        return;
    }
    
    // Convert to decimal, divide, then convert back
    long long decimalA = toDecimal(a, aLen);
    long long decimalB = toDecimal(b, bLen);
    
    if (decimalA < decimalB) {
        quotient[0] = 0;
        *quotientLen = 1;
        int i = 0;
        while (i < aLen) {
            remainder[i] = a[i];
            i++;
        }
        *remainderLen = aLen;
        return;
    }
    
    long long quotientDecimal = decimalA / decimalB;
    long long remainderDecimal = decimalA % decimalB;
    
    fromDecimal(quotientDecimal, quotient, quotientLen);
    fromDecimal(remainderDecimal, remainder, remainderLen);
}

// Compare two digit arrays (returns -1 if a < b, 0 if a == b, 1 if a > b)
int compareDigits(int a[], int aLen, int b[], int bLen) {
    if (aLen != bLen) {
        return (aLen > bLen) ? 1 : -1;
    }
    
    return compareDigitsRecursive(a, b, 0, aLen);
}

int compareDigitsRecursive(int a[], int b[], int pos, int len) {
    if (pos >= len) return 0;
    
    if (a[pos] != b[pos]) {
        return (a[pos] > b[pos]) ? 1 : -1;
    }
    
    return compareDigitsRecursive(a, b, pos + 1, len);
}

// Parse input string to digit array
void parseNumber(const char* input, int digits[], int* length) {
    *length = 0;
    int i = 0;
    while (input[i] != '\0' && *length < MAX_DIGITS) {
        int digit = getDigitValue(input[i]);
        if (digit < 0 || digit >= base) {
            printf("Error: Invalid digit for base %d\n", base);
            return;
        }
        digits[(*length)++] = digit;
        i++;
    }
    
    if (*length > MAX_DIGITS) {
        printf("Error: Number exceeds maximum %d digits\n", MAX_DIGITS);
        return;
    }
    
    // Handle empty input
    if (*length == 0) {
        digits[0] = 0;
        *length = 1;
    }
}

// Convert digit array to string
void toString(int digits[], int length, char* result) {
    if (length == 0) {
        result[0] = '0';
        result[1] = '\0';
        return;
    }
    
    int i = 0;
    while (i < length) {
        result[i] = getDigitChar(digits[i]);
        i++;
    }
    result[length] = '\0';
}

// Addition operation
void add(int a[], int aLen, int b[], int bLen, int result[], int* resultLen) {
    addDigits(a, aLen, b, bLen, result, resultLen);
}

// Subtraction operation
void subtract(int a[], int aLen, int b[], int bLen, int result[], int* resultLen) {
    if (compareDigits(a, aLen, b, bLen) < 0) {
        printf("Subtraction Error: Result would be negative\n");
        return;
    }
    subtractDigits(a, aLen, b, bLen, result, resultLen);
}

// Multiplication operation
void multiply(int a[], int aLen, int b[], int bLen, int result[], int* resultLen) {
    multiplyDigits(a, aLen, b, bLen, result, resultLen);
}

// Division operation
void divide(int a[], int aLen, int b[], int bLen, int quotient[], int* quotientLen, int remainder[], int* remainderLen) {
    // Check for division by zero
    if (bLen == 0 || (bLen == 1 && b[0] == 0)) {
        printf("Division Error: Division by zero\n");
        quotient[0] = 0;
        *quotientLen = 0;
        remainder[0] = 0;
        *remainderLen = 0;
        return;
    }
    divideDigits(a, aLen, b, bLen, quotient, quotientLen, remainder, remainderLen);
}

int main() {
    printf("=== Advanced Multi-Base Arithmetic Engine ===\n");
    printf("Supports bases 2-16 with up to 10-digit numbers\n");
    printf("=============================================\n");
    
    // Get base from user
    printf("Enter the numeral system base (2-16): ");
    scanf("%d", &base);
    
    if (base < 2 || base > 16) {
        printf("Error: Base must be between 2 and 16\n");
        return 1;
    }
    
    // Get first number
    char input1[20];
    printf("Enter first number (base %d): ", base);
    scanf("%s", input1);
    
    int num1[MAX_DIGITS];
    int num1Len;
    parseNumber(input1, num1, &num1Len);
    
    // Get second number
    char input2[20];
    printf("Enter second number (base %d): ", base);
    scanf("%s", input2);
    
    int num2[MAX_DIGITS];
    int num2Len;
    parseNumber(input2, num2, &num2Len);
    
    // Check if parsing was successful
    if (num1Len == 0 || num2Len == 0) {
        printf("Error: Invalid input\n");
        return 1;
    }
    
    printf("\n=== Results (Base %d) ===\n", base);
    
    // Addition
    int sum[MAX_DIGITS * 2];
    int sumLen;
    add(num1, num1Len, num2, num2Len, sum, &sumLen);
    
    char num1Str[20], num2Str[20], sumStr[20];
    toString(num1, num1Len, num1Str);
    toString(num2, num2Len, num2Str);
    toString(sum, sumLen, sumStr);
    
    printf("Addition: %s + %s = %s\n", num1Str, num2Str, sumStr);
    
    // Subtraction
    int diff[MAX_DIGITS * 2];
    int diffLen;
    subtract(num1, num1Len, num2, num2Len, diff, &diffLen);
    
    char diffStr[20];
    toString(diff, diffLen, diffStr);
    
    printf("Subtraction: %s - %s = %s\n", num1Str, num2Str, diffStr);
    
    // Multiplication
    int product[MAX_DIGITS * 2];
    int productLen;
    multiply(num1, num1Len, num2, num2Len, product, &productLen);
    
    char productStr[20];
    toString(product, productLen, productStr);
    
    printf("Multiplication: %s * %s = %s\n", num1Str, num2Str, productStr);
    
    // Division
    int quotient[MAX_DIGITS * 2], remainder[MAX_DIGITS * 2];
    int quotientLen, remainderLen;
    divide(num1, num1Len, num2, num2Len, quotient, &quotientLen, remainder, &remainderLen);
    
    if (quotientLen > 0) {
        char quotientStr[20], remainderStr[20];
        toString(quotient, quotientLen, quotientStr);
        toString(remainder, remainderLen, remainderStr);
        
        printf("Division: %s / %s = %s (remainder: %s)\n", num1Str, num2Str, quotientStr, remainderStr);
    } else {
        printf("Division: %s / %s = Error\n", num1Str, num2Str);
    }
    
    return 0;
}