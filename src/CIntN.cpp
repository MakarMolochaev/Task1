#include "CIntN.h"
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <string>

CIntN::CIntN() : length(1) {
    memset(digits, 0, N);
}

CIntN::CIntN(unsigned long long value) {
    memset(digits, 0, N);
    length = 0;
    
    if (value == 0) {
        length = 1;
        return;
    }
    
    while (value > 0 && length < N) {
        digits[length++] = value % 10;
        value /= 10;
    }
}

CIntN::CIntN(const char* str) {
    if (str == nullptr) {
        throw std::invalid_argument("Null pointer passed to constructor");
    }
    
    memset(digits, 0, N);
    int strLen = strlen(str);
    
    if (strLen == 0) {
        length = 1;
        return;
    }
    
    for (int i = 0; i < strLen; i++) {
        if (str[i] < '0' || str[i] > '9') {
            throw std::invalid_argument("Invalid character in number string");
        }
    }
    
    length = strLen;
    if (length > N) {
        throw std::out_of_range("Number too large for CIntN");
    }
    
    for (int i = 0; i < length; i++) {
        digits[length - 1 - i] = str[i] - '0';
    }
    
    normalize();
}


CIntN::CIntN(const CIntN& other) : length(other.length) {
    memcpy(digits, other.digits, N);
}


CIntN& CIntN::operator=(const CIntN& other) {
    if (this != &other) {
        length = other.length;
        memcpy(digits, other.digits, N);
    }
    return *this;
}

CIntN& CIntN::operator=(unsigned long long value) {
    *this = CIntN(value);
    return *this;
}

CIntN CIntN::operator+(const CIntN& other) const {
    CIntN result;
    int maxLen = (length > other.length) ? length : other.length;
    
    if (maxLen >= N) {
        throw std::overflow_error("Addition would exceed maximum number length");
    }
    
    int carry = 0;
    for (int i = 0; i < maxLen || carry; i++) {
        if (i >= N) {
            throw std::overflow_error("Addition overflow");
        }
        
        int sum = digits[i] + other.digits[i] + carry;
        result.digits[i] = sum % 10;
        carry = sum / 10;
        result.length = i + 1;
    }
    
    result.normalize();
    return result;
}


CIntN CIntN::operator-(const CIntN& other) const {
    if (*this < other) {
        throw std::underflow_error("Subtraction would result in negative number");
    }
    
    CIntN result;
    int borrow = 0;
    
    for (int i = 0; i < length; i++) {
        int diff = digits[i] - other.digits[i] - borrow;
        
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.digits[i] = diff;
        result.length = i + 1;
    }
    
    result.normalize();
    return result;
}

bool CIntN::operator==(const CIntN& other) const {
    if (length != other.length) return false;
    
    for (int i = 0; i < length; i++) {
        if (digits[i] != other.digits[i]) return false;
    }
    
    return true;
}

bool CIntN::operator!=(const CIntN& other) const {
    return !(*this == other);
}

bool CIntN::operator<(const CIntN& other) const {
    if (length != other.length) {
        return length < other.length;
    }
    
    for (int i = length - 1; i >= 0; i--) {
        if (digits[i] != other.digits[i]) {
            return digits[i] < other.digits[i];
        }
    }
    
    return false;
}

bool CIntN::operator>(const CIntN& other) const {
    return other < *this;
}

bool CIntN::operator<=(const CIntN& other) const {
    return !(other < *this);
}

bool CIntN::operator>=(const CIntN& other) const {
    return !(*this < other);
}

void CIntN::print() const {
    for (int i = length - 1; i >= 0; i--) {
        std::cout << (int)digits[i];
    }
}

std::string CIntN::toString() const {
    std::string result;
    for (int i = length - 1; i >= 0; i--) {
        result += (char)('0' + digits[i]);
    }
    return result;
}

bool CIntN::isZero() const {
    return length == 1 && digits[0] == 0;
}

void CIntN::normalize() {
    while (length > 1 && digits[length - 1] == 0) {
        length--;
    }
}