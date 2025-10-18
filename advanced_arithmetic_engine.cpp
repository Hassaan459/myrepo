#include <iostream>
#include <cmath>

class MultiBaseArithmetic {
private:
    static const int MAX_DIGITS = 10;
    int base;
    
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
    
    // Convert multi-base number to decimal using recursive approach
    long long toDecimal(int digits[], int length) {
        if (length == 0) return 0;
        if (length == 1) return digits[0];
        
        // Use recursive approach instead of loops
        return toDecimalRecursive(digits, 0, length - 1);
    }
    
    long long toDecimalRecursive(int digits[], int start, int end) {
        if (start > end) return 0;
        if (start == end) return digits[start];
        
        int mid = start + (end - start) / 2;
        long long left = toDecimalRecursive(digits, start, mid);
        long long right = toDecimalRecursive(digits, mid + 1, end);
        
        // Combine results: left * base^(end-mid) + right
        long long power = 1;
        for (int i = 0; i < end - mid; i++) {
            power *= base;
        }
        
        return left * power + right;
    }
    
    // Convert decimal to multi-base using recursive approach
    void fromDecimal(long long decimal, int result[], int& length) {
        if (decimal == 0) {
            result[0] = 0;
            length = 1;
            return;
        }
        
        length = 0;
        fromDecimalRecursive(decimal, result, length);
    }
    
    void fromDecimalRecursive(long long decimal, int result[], int& length) {
        if (decimal == 0) return;
        
        fromDecimalRecursive(decimal / base, result, length);
        result[length++] = decimal % base;
    }
    
    // Add two digit arrays
    void addDigits(int a[], int aLen, int b[], int bLen, int result[], int& resultLen) {
        int carry = 0;
        int maxLen = (aLen > bLen) ? aLen : bLen;
        
        // Pad shorter number with zeros
        int paddedA[MAX_DIGITS];
        int paddedB[MAX_DIGITS];
        int paddedALen = maxLen;
        int paddedBLen = maxLen;
        
        // Pad a
        int aOffset = maxLen - aLen;
        for (int i = 0; i < aOffset; i++) {
            paddedA[i] = 0;
        }
        for (int i = 0; i < aLen; i++) {
            paddedA[i + aOffset] = a[i];
        }
        
        // Pad b
        int bOffset = maxLen - bLen;
        for (int i = 0; i < bOffset; i++) {
            paddedB[i] = 0;
        }
        for (int i = 0; i < bLen; i++) {
            paddedB[i + bOffset] = b[i];
        }
        
        // Add digits from right to left using recursive approach
        resultLen = 0;
        addDigitsRecursive(paddedA, paddedB, maxLen - 1, carry, result, resultLen);
        
        if (carry > 0) {
            // Shift result right and add carry at beginning
            for (int i = resultLen; i > 0; i--) {
                result[i] = result[i-1];
            }
            result[0] = carry;
            resultLen++;
        }
    }
    
    void addDigitsRecursive(int a[], int b[], int pos, int& carry, int result[], int& resultLen) {
        if (pos < 0) return;
        
        int sum = a[pos] + b[pos] + carry;
        carry = sum / base;
        int digit = sum % base;
        
        addDigitsRecursive(a, b, pos - 1, carry, result, resultLen);
        result[resultLen++] = digit;
    }
    
    // Subtract two digit arrays (assumes a >= b)
    void subtractDigits(int a[], int aLen, int b[], int bLen, int result[], int& resultLen) {
        int borrow = 0;
        int maxLen = (aLen > bLen) ? aLen : bLen;
        
        // Pad shorter number with zeros
        int paddedA[MAX_DIGITS];
        int paddedB[MAX_DIGITS];
        int paddedALen = maxLen;
        int paddedBLen = maxLen;
        
        // Pad a
        int aOffset = maxLen - aLen;
        for (int i = 0; i < aOffset; i++) {
            paddedA[i] = 0;
        }
        for (int i = 0; i < aLen; i++) {
            paddedA[i + aOffset] = a[i];
        }
        
        // Pad b
        int bOffset = maxLen - bLen;
        for (int i = 0; i < bOffset; i++) {
            paddedB[i] = 0;
        }
        for (int i = 0; i < bLen; i++) {
            paddedB[i + bOffset] = b[i];
        }
        
        // Subtract digits from right to left using recursive approach
        resultLen = 0;
        subtractDigitsRecursive(paddedA, paddedB, maxLen - 1, borrow, result, resultLen);
        
        // Remove leading zeros
        while (resultLen > 1 && result[0] == 0) {
            for (int i = 0; i < resultLen - 1; i++) {
                result[i] = result[i + 1];
            }
            resultLen--;
        }
    }
    
    void subtractDigitsRecursive(int a[], int b[], int pos, int& borrow, int result[], int& resultLen) {
        if (pos < 0) return;
        
        int diff = a[pos] - b[pos] - borrow;
        if (diff < 0) {
            diff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        subtractDigitsRecursive(a, b, pos - 1, borrow, result, resultLen);
        result[resultLen++] = diff;
    }
    
    // Multiply two digit arrays using iterative approach to avoid stack overflow
    void multiplyDigits(int a[], int aLen, int b[], int bLen, int result[], int& resultLen) {
        if (aLen == 0 || bLen == 0) {
            result[0] = 0;
            resultLen = 1;
            return;
        }
        if (aLen == 1 && a[0] == 0) {
            result[0] = 0;
            resultLen = 1;
            return;
        }
        if (bLen == 1 && b[0] == 0) {
            result[0] = 0;
            resultLen = 1;
            return;
        }
        if (aLen == 1 && a[0] == 1) {
            for (int i = 0; i < bLen; i++) {
                result[i] = b[i];
            }
            resultLen = bLen;
            return;
        }
        if (bLen == 1 && b[0] == 1) {
            for (int i = 0; i < aLen; i++) {
                result[i] = a[i];
            }
            resultLen = aLen;
            return;
        }
        
        // Convert to decimal, multiply, then convert back
        // This is more reliable for large numbers
        long long decimalA = toDecimal(a, aLen);
        long long decimalB = toDecimal(b, bLen);
        long long product = decimalA * decimalB;
        
        fromDecimal(product, result, resultLen);
    }
    
    
    // Divide two digit arrays using recursive approach
    void divideDigits(int a[], int aLen, int b[], int bLen, int quotient[], int& quotientLen, int remainder[], int& remainderLen) {
        if (bLen == 0 || (bLen == 1 && b[0] == 0)) {
            throw std::runtime_error("Division by zero");
        }
        
        // Convert to decimal, divide, then convert back
        long long decimalA = toDecimal(a, aLen);
        long long decimalB = toDecimal(b, bLen);
        
        if (decimalA < decimalB) {
            quotient[0] = 0;
            quotientLen = 1;
            for (int i = 0; i < aLen; i++) {
                remainder[i] = a[i];
            }
            remainderLen = aLen;
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

public:
    MultiBaseArithmetic(int base) : base(base) {
        if (base < 2 || base > 16) {
            throw std::invalid_argument("Base must be between 2 and 16");
        }
    }
    
    // Parse input string to digit array
    void parseNumber(const char* input, int digits[], int& length) {
        length = 0;
        for (int i = 0; input[i] != '\0' && length < MAX_DIGITS; i++) {
            int digit = getDigitValue(input[i]);
            if (digit < 0 || digit >= base) {
                throw std::invalid_argument("Invalid digit for base " + std::to_string(base));
            }
            digits[length++] = digit;
        }
        
        if (length > MAX_DIGITS) {
            throw std::invalid_argument("Number exceeds maximum " + std::to_string(MAX_DIGITS) + " digits");
        }
    }
    
    // Convert digit array to string
    void toString(int digits[], int length, char* result) {
        if (length == 0) {
            result[0] = '0';
            result[1] = '\0';
            return;
        }
        
        for (int i = 0; i < length; i++) {
            result[i] = getDigitChar(digits[i]);
        }
        result[length] = '\0';
    }
    
    // Addition operation
    void add(int a[], int aLen, int b[], int bLen, int result[], int& resultLen) {
        addDigits(a, aLen, b, bLen, result, resultLen);
    }
    
    // Subtraction operation
    void subtract(int a[], int aLen, int b[], int bLen, int result[], int& resultLen) {
        if (compareDigits(a, aLen, b, bLen) < 0) {
            throw std::runtime_error("Result would be negative");
        }
        subtractDigits(a, aLen, b, bLen, result, resultLen);
    }
    
    // Multiplication operation
    void multiply(int a[], int aLen, int b[], int bLen, int result[], int& resultLen) {
        multiplyDigits(a, aLen, b, bLen, result, resultLen);
    }
    
    // Division operation
    void divide(int a[], int aLen, int b[], int bLen, int quotient[], int& quotientLen, int remainder[], int& remainderLen) {
        divideDigits(a, aLen, b, bLen, quotient, quotientLen, remainder, remainderLen);
    }
};

int main() {
    std::cout << "=== Advanced Multi-Base Arithmetic Engine ===" << std::endl;
    std::cout << "Supports bases 2-16 with up to 10-digit numbers" << std::endl;
    std::cout << "=============================================" << std::endl;
    
    try {
        // Get base from user
        int base;
        std::cout << "Enter the numeral system base (2-16): ";
        std::cin >> base;
        
        if (base < 2 || base > 16) {
            std::cout << "Error: Base must be between 2 and 16" << std::endl;
            return 1;
        }
        
        MultiBaseArithmetic engine(base);
        
        // Get first number
        char input1[20];
        std::cout << "Enter first number (base " << base << "): ";
        std::cin >> input1;
        
        int num1[10];
        int num1Len;
        engine.parseNumber(input1, num1, num1Len);
        
        // Get second number
        char input2[20];
        std::cout << "Enter second number (base " << base << "): ";
        std::cin >> input2;
        
        int num2[10];
        int num2Len;
        engine.parseNumber(input2, num2, num2Len);
        
        std::cout << "\n=== Results (Base " << base << ") ===" << std::endl;
        
        // Addition
        try {
            int sum[20];
            int sumLen;
            engine.add(num1, num1Len, num2, num2Len, sum, sumLen);
            
            char num1Str[20], num2Str[20], sumStr[20];
            engine.toString(num1, num1Len, num1Str);
            engine.toString(num2, num2Len, num2Str);
            engine.toString(sum, sumLen, sumStr);
            
            std::cout << "Addition: " << num1Str << " + " << num2Str << " = " << sumStr << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Addition Error: " << e.what() << std::endl;
        }
        
        // Subtraction
        try {
            int diff[20];
            int diffLen;
            engine.subtract(num1, num1Len, num2, num2Len, diff, diffLen);
            
            char num1Str[20], num2Str[20], diffStr[20];
            engine.toString(num1, num1Len, num1Str);
            engine.toString(num2, num2Len, num2Str);
            engine.toString(diff, diffLen, diffStr);
            
            std::cout << "Subtraction: " << num1Str << " - " << num2Str << " = " << diffStr << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Subtraction Error: " << e.what() << std::endl;
        }
        
        // Multiplication
        try {
            int product[20];
            int productLen;
            engine.multiply(num1, num1Len, num2, num2Len, product, productLen);
            
            char num1Str[20], num2Str[20], productStr[20];
            engine.toString(num1, num1Len, num1Str);
            engine.toString(num2, num2Len, num2Str);
            engine.toString(product, productLen, productStr);
            
            std::cout << "Multiplication: " << num1Str << " * " << num2Str << " = " << productStr << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Multiplication Error: " << e.what() << std::endl;
        }
        
        // Division
        try {
            int quotient[20], remainder[20];
            int quotientLen, remainderLen;
            engine.divide(num1, num1Len, num2, num2Len, quotient, quotientLen, remainder, remainderLen);
            
            char num1Str[20], num2Str[20], quotientStr[20], remainderStr[20];
            engine.toString(num1, num1Len, num1Str);
            engine.toString(num2, num2Len, num2Str);
            engine.toString(quotient, quotientLen, quotientStr);
            engine.toString(remainder, remainderLen, remainderStr);
            
            std::cout << "Division: " << num1Str << " / " << num2Str << " = " << quotientStr 
                      << " (remainder: " << remainderStr << ")" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Division Error: " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}