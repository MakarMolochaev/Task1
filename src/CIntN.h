#ifndef CINTN_H
#define CINTN_H

#include <string>

#define N 50

class CIntN {
private:
    unsigned char digits[N];
    int length;

public:
    CIntN();
    CIntN(unsigned long long value);
    CIntN(const char* str);
    CIntN(const CIntN& other);
    
    CIntN& operator=(const CIntN& other);
    CIntN& operator=(unsigned long long value);
    
    CIntN operator+(const CIntN& other) const;
    CIntN operator-(const CIntN& other) const;
    
    bool operator==(const CIntN& other) const;
    bool operator!=(const CIntN& other) const;
    bool operator<(const CIntN& other) const;
    bool operator>(const CIntN& other) const;
    bool operator<=(const CIntN& other) const;
    bool operator>=(const CIntN& other) const;
    
    void print() const;
    std::string toString() const;
    int getLength() const { return length; }
    
    bool isZero() const;
    
private:
    void normalize();
};

#endif // CINTN_H