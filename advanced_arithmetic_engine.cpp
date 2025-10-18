#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

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
    long long toDecimal(const std::vector<int>& digits) {
        if (digits.empty()) return 0;
        
        // Use recursive approach instead of loops
        return toDecimalRecursive(digits, 0, digits.size() - 1);
    }
    
    long long toDecimalRecursive(const std::vector<int>& digits, int start, int end) {
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
    std::vector<int> fromDecimal(long long decimal) {
        if (decimal == 0) return {0};
        
        std::vector<int> result;
        fromDecimalRecursive(decimal, result);
        return result;
    }
    
    void fromDecimalRecursive(long long decimal, std::vector<int>& result) {
        if (decimal == 0) return;
        
        fromDecimalRecursive(decimal / base, result);
        result.push_back(decimal % base);
    }
    
    // Add two digit arrays
    std::vector<int> addDigits(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> result;
        int carry = 0;
        int maxLen = std::max(a.size(), b.size());
        
        // Pad shorter number with zeros
        std::vector<int> paddedA = a;
        std::vector<int> paddedB = b;
        
        while (paddedA.size() < maxLen) paddedA.insert(paddedA.begin(), 0);
        while (paddedB.size() < maxLen) paddedB.insert(paddedB.begin(), 0);
        
        // Add digits from right to left using recursive approach
        addDigitsRecursive(paddedA, paddedB, maxLen - 1, carry, result);
        
        if (carry > 0) {
            result.insert(result.begin(), carry);
        }
        
        return result;
    }
    
    void addDigitsRecursive(const std::vector<int>& a, const std::vector<int>& b, 
                           int pos, int& carry, std::vector<int>& result) {
        if (pos < 0) return;
        
        int sum = a[pos] + b[pos] + carry;
        carry = sum / base;
        int digit = sum % base;
        
        addDigitsRecursive(a, b, pos - 1, carry, result);
        result.push_back(digit);
    }
    
    // Subtract two digit arrays (assumes a >= b)
    std::vector<int> subtractDigits(const std::vector<int>& a, const std::vector<int>& b) {
        std::vector<int> result;
        int borrow = 0;
        int maxLen = std::max(a.size(), b.size());
        
        // Pad shorter number with zeros
        std::vector<int> paddedA = a;
        std::vector<int> paddedB = b;
        
        while (paddedA.size() < maxLen) paddedA.insert(paddedA.begin(), 0);
        while (paddedB.size() < maxLen) paddedB.insert(paddedB.begin(), 0);
        
        // Subtract digits from right to left using recursive approach
        subtractDigitsRecursive(paddedA, paddedB, maxLen - 1, borrow, result);
        
        // Remove leading zeros
        while (result.size() > 1 && result[0] == 0) {
            result.erase(result.begin());
        }
        
        return result;
    }
    
    void subtractDigitsRecursive(const std::vector<int>& a, const std::vector<int>& b,
                                int pos, int& borrow, std::vector<int>& result) {
        if (pos < 0) return;
        
        int diff = a[pos] - b[pos] - borrow;
        if (diff < 0) {
            diff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        subtractDigitsRecursive(a, b, pos - 1, borrow, result);
        result.push_back(diff);
    }
    
    // Multiply two digit arrays using recursive approach
    std::vector<int> multiplyDigits(const std::vector<int>& a, const std::vector<int>& b) {
        if (a.empty() || b.empty()) return {0};
        if (a.size() == 1 && a[0] == 0) return {0};
        if (b.size() == 1 && b[0] == 0) return {0};
        if (a.size() == 1 && a[0] == 1) return b;
        if (b.size() == 1 && b[0] == 1) return a;
        
        // Use digit-by-digit multiplication to avoid overflow
        return multiplyDigitsRecursive(a, b);
    }
    
    std::vector<int> multiplyDigitsRecursive(const std::vector<int>& a, const std::vector<int>& b) {
        if (a.size() == 1) {
            return multiplyByDigit(b, a[0]);
        }
        if (b.size() == 1) {
            return multiplyByDigit(a, b[0]);
        }
        
        // Split the larger number and use distributive property
        if (a.size() >= b.size()) {
            int mid = a.size() / 2;
            std::vector<int> aHigh(a.begin(), a.begin() + mid);
            std::vector<int> aLow(a.begin() + mid, a.end());
            
            std::vector<int> term1 = multiplyDigitsRecursive(aHigh, b);
            std::vector<int> term2 = multiplyDigitsRecursive(aLow, b);
            
            // Shift term1 by appropriate number of positions
            for (int i = 0; i < a.size() - mid; i++) {
                term1.push_back(0);
            }
            
            return addDigits(term1, term2);
        } else {
            return multiplyDigitsRecursive(b, a);
        }
    }
    
    std::vector<int> multiplyByDigit(const std::vector<int>& a, int digit) {
        if (digit == 0) return {0};
        if (digit == 1) return a;
        
        std::vector<int> result;
        int carry = 0;
        
        multiplyByDigitRecursive(a, digit, a.size() - 1, carry, result);
        
        if (carry > 0) {
            result.insert(result.begin(), carry);
        }
        
        return result;
    }
    
    void multiplyByDigitRecursive(const std::vector<int>& a, int digit, int pos, int& carry, std::vector<int>& result) {
        if (pos < 0) return;
        
        int product = a[pos] * digit + carry;
        carry = product / base;
        int resultDigit = product % base;
        
        multiplyByDigitRecursive(a, digit, pos - 1, carry, result);
        result.push_back(resultDigit);
    }
    
    // Divide two digit arrays using recursive approach
    std::pair<std::vector<int>, std::vector<int>> divideDigits(const std::vector<int>& a, const std::vector<int>& b) {
        if (b.empty() || (b.size() == 1 && b[0] == 0)) {
            throw std::runtime_error("Division by zero");
        }
        
        // Convert to decimal, divide, then convert back
        long long decimalA = toDecimal(a);
        long long decimalB = toDecimal(b);
        
        if (decimalA < decimalB) {
            return {{0}, a}; // quotient = 0, remainder = a
        }
        
        long long quotient = decimalA / decimalB;
        long long remainder = decimalA % decimalB;
        
        return {fromDecimal(quotient), fromDecimal(remainder)};
    }
    
    // Compare two digit arrays (returns -1 if a < b, 0 if a == b, 1 if a > b)
    int compareDigits(const std::vector<int>& a, const std::vector<int>& b) {
        if (a.size() != b.size()) {
            return (a.size() > b.size()) ? 1 : -1;
        }
        
        return compareDigitsRecursive(a, b, 0);
    }
    
    int compareDigitsRecursive(const std::vector<int>& a, const std::vector<int>& b, int pos) {
        if (pos >= a.size()) return 0;
        
        if (a[pos] != b[pos]) {
            return (a[pos] > b[pos]) ? 1 : -1;
        }
        
        return compareDigitsRecursive(a, b, pos + 1);
    }

public:
    MultiBaseArithmetic(int base) : base(base) {
        if (base < 2 || base > 16) {
            throw std::invalid_argument("Base must be between 2 and 16");
        }
    }
    
    // Parse input string to digit array
    std::vector<int> parseNumber(const std::string& input) {
        std::vector<int> digits;
        
        for (char c : input) {
            int digit = getDigitValue(c);
            if (digit < 0 || digit >= base) {
                throw std::invalid_argument("Invalid digit for base " + std::to_string(base));
            }
            digits.push_back(digit);
        }
        
        if (digits.size() > MAX_DIGITS) {
            throw std::invalid_argument("Number exceeds maximum " + std::to_string(MAX_DIGITS) + " digits");
        }
        
        return digits;
    }
    
    // Convert digit array to string
    std::string toString(const std::vector<int>& digits) {
        if (digits.empty()) return "0";
        
        std::string result;
        for (int digit : digits) {
            result += getDigitChar(digit);
        }
        return result;
    }
    
    // Addition operation
    std::vector<int> add(const std::vector<int>& a, const std::vector<int>& b) {
        return addDigits(a, b);
    }
    
    // Subtraction operation
    std::vector<int> subtract(const std::vector<int>& a, const std::vector<int>& b) {
        if (compareDigits(a, b) < 0) {
            throw std::runtime_error("Result would be negative");
        }
        return subtractDigits(a, b);
    }
    
    // Multiplication operation
    std::vector<int> multiply(const std::vector<int>& a, const std::vector<int>& b) {
        return multiplyDigits(a, b);
    }
    
    // Division operation
    std::pair<std::vector<int>, std::vector<int>> divide(const std::vector<int>& a, const std::vector<int>& b) {
        return divideDigits(a, b);
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
        std::string input1;
        std::cout << "Enter first number (base " << base << "): ";
        std::cin >> input1;
        
        std::vector<int> num1 = engine.parseNumber(input1);
        
        // Get second number
        std::string input2;
        std::cout << "Enter second number (base " << base << "): ";
        std::cin >> input2;
        
        std::vector<int> num2 = engine.parseNumber(input2);
        
        std::cout << "\n=== Results (Base " << base << ") ===" << std::endl;
        
        // Addition
        try {
            std::vector<int> sum = engine.add(num1, num2);
            std::cout << "Addition: " << engine.toString(num1) << " + " << engine.toString(num2) 
                      << " = " << engine.toString(sum) << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Addition Error: " << e.what() << std::endl;
        }
        
        // Subtraction
        try {
            std::vector<int> diff = engine.subtract(num1, num2);
            std::cout << "Subtraction: " << engine.toString(num1) << " - " << engine.toString(num2) 
                      << " = " << engine.toString(diff) << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Subtraction Error: " << e.what() << std::endl;
        }
        
        // Multiplication
        try {
            std::vector<int> product = engine.multiply(num1, num2);
            std::cout << "Multiplication: " << engine.toString(num1) << " * " << engine.toString(num2) 
                      << " = " << engine.toString(product) << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Multiplication Error: " << e.what() << std::endl;
        }
        
        // Division
        try {
            auto [quotient, remainder] = engine.divide(num1, num2);
            std::cout << "Division: " << engine.toString(num1) << " / " << engine.toString(num2) 
                      << " = " << engine.toString(quotient) << " (remainder: " << engine.toString(remainder) << ")" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Division Error: " << e.what() << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}