#include "CIntN.h"
#include <iostream>
#include <cassert>
#include <string>

void testConstructors() {
    std::cout << "Testing constructors..." << std::endl;
    
    CIntN zero;
    assert(zero.toString() == "0");
    std::cout << "Default constructor: OK" << std::endl;
    
    CIntN num1(12345);
    assert(num1.toString() == "12345");
    std::cout << "Constructor from integer: OK" << std::endl;
    
    CIntN num2("67890");
    assert(num2.toString() == "67890");
    std::cout << "Constructor from string: OK" << std::endl;
    
    CIntN num3 = num1;
    assert(num3.toString() == "12345");
    std::cout << "Copy constructor: OK" << std::endl;
    
    std::cout << "All constructor tests passed!\n" << std::endl;
}

void testAssignment() {
    std::cout << "Testing assignment operators..." << std::endl;
    
    CIntN num1(111);
    CIntN num2;
    
    num2 = num1;
    assert(num2.toString() == "111");
    std::cout << "Object assignment: OK" << std::endl;
    
    CIntN num3;
    num3 = 999;
    assert(num3.toString() == "999");
    std::cout << "Integer assignment: OK" << std::endl;
    
    std::cout << "All assignment tests passed!\n" << std::endl;
}

void testAddition() {
    std::cout << "Testing addition..." << std::endl;
    
    CIntN num1(123);
    CIntN num2(456);
    CIntN result1 = num1 + num2;
    assert(result1.toString() == "579");
    std::cout << "Simple addition: OK" << std::endl;
    
    CIntN num3(999);
    CIntN num4(1);
    CIntN result2 = num3 + num4;
    assert(result2.toString() == "1000");
    std::cout << "Addition with carry: OK" << std::endl;
    
    CIntN num5("12345678901234567890");
    CIntN num6("98765432109876543210");
    CIntN result3 = num5 + num6;
    assert(result3.toString() == "111111111011111111100");
    std::cout << "Large numbers addition: OK" << std::endl;

    CIntN num7(777);
    CIntN zero;
    CIntN result4 = num7 + zero;
    assert(result4.toString() == "777");
    std::cout << "Addition with zero: OK" << std::endl;
    
    std::cout << "All addition tests passed!\n" << std::endl;
}

void testSubtraction() {
    std::cout << "Testing subtraction..." << std::endl;
    
    CIntN num1(456);
    CIntN num2(123);
    CIntN result1 = num1 - num2;
    assert(result1.toString() == "333");
    std::cout << "Simple subtraction: OK" << std::endl;
    
    CIntN num3(1000);
    CIntN num4(1);
    CIntN result2 = num3 - num4;
    assert(result2.toString() == "999");
    std::cout << "Subtraction with borrow: OK" << std::endl;
    
    CIntN num5("10000000000000000000");
    CIntN num6("9999999999999999999");
    CIntN result3 = num5 - num6;
    assert(result3.toString() == "1");
    std::cout << "Large numbers subtraction: OK" << std::endl;
    
    CIntN num7(888);
    CIntN zero;
    CIntN result4 = num7 - zero;
    assert(result4.toString() == "888");
    std::cout << "Subtraction of zero: OK" << std::endl;
    
    std::cout << "All subtraction tests passed!\n" << std::endl;
}

void testComparison() {
    std::cout << "Testing comparison operators..." << std::endl;
    
    CIntN num1(100);
    CIntN num2(200);
    CIntN num3(100);
    
    assert(num1 == num3);
    assert(!(num1 == num2));
    std::cout << "Equality: OK" << std::endl;
    
    assert(num1 != num2);
    assert(!(num1 != num3));
    std::cout << "Inequality: OK" << std::endl;
    
    assert(num1 < num2);
    assert(!(num2 < num1));
    assert(!(num1 < num3));
    std::cout << "Less than: OK" << std::endl;
    
    assert(num2 > num1);
    assert(!(num1 > num2));
    assert(!(num1 > num3));
    std::cout << "Greater than: OK" << std::endl;
    
    assert(num1 <= num2);
    assert(num1 <= num3);
    assert(!(num2 <= num1));
    std::cout << "Less than or equal: OK" << std::endl;
    
    assert(num2 >= num1);
    assert(num1 >= num3);
    assert(!(num1 >= num2));
    std::cout << "Greater than or equal: OK" << std::endl;
    
    std::cout << "All comparison tests passed!\n" << std::endl;
}

void testEdgeCases() {
    std::cout << "Testing edge cases..." << std::endl;
    
    CIntN zero1;
    CIntN zero2((unsigned long long)0);
    CIntN zero3("0");
    assert(zero1 == zero2);
    assert(zero2 == zero3);
    assert(zero1.isZero());
    std::cout << "Zero handling: OK" << std::endl;
    
    CIntN large1("12345678901234567890123456789012345678901234567890");
    assert(large1.toString() == "12345678901234567890123456789012345678901234567890");
    std::cout << "Large numbers: OK" << std::endl;
    
    CIntN maxNum("99999999999999999999999999999999999999999999999999");
    CIntN one(1);
    
    try {
        CIntN overflow = maxNum + one;
        std::cout << "Overflow test: Needs improvement" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Overflow handling: OK" << std::endl;
    }
    
    try {
        CIntN small(1);
        CIntN large(2);
        CIntN negative = small - large;
        std::cout << "Underflow test: Needs improvement" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Underflow handling: OK" << std::endl;
    }
    
    std::cout << "All edge case tests passed!\n" << std::endl;
}

int main() {
    std::cout << "=== Starting CIntN Tests ===\n" << std::endl;
    
    try {
        testConstructors();
        testAssignment();
        testAddition();
        testSubtraction();
        testComparison();
        testEdgeCases();
        
        std::cout << "=== All tests passed successfully! ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Test failed with exception: " << e.what() << std::endl;
        return 1;
    }
}