#include "timespec.h"
#include <iostream>
#include <iomanip>
#include <cmath>

// Helper function to print a timespec value
void print_timespec(const std::string& label, const timespec& ts) {
    std::cout << label << ": tv_sec = " << ts.tv_sec 
              << ", tv_nsec = " << ts.tv_nsec << std::endl;
}

// Helper function to check if timespec is normalized
bool is_normalized(const timespec& ts) {
    return (ts.tv_nsec >= 0 && ts.tv_nsec < 1000000000);
}

// Helper function to compare two timespec values
bool timespec_equal(const timespec& ts1, const timespec& ts2) {
    return (ts1.tv_sec == ts2.tv_sec && ts1.tv_nsec == ts2.tv_nsec);
}

void test_timespec_to_ms() {
    std::cout << "\n=== Testing timespec_to_ms ===" << std::endl;
    
    // Test case 1: Positive time (2.7 seconds)
    timespec ts1 = {2, 700000000};
    double ms1 = timespec_to_ms(ts1);
    print_timespec("Input", ts1);
    std::cout << "Output: " << ms1 << " microseconds (expected: 2700000)" << std::endl;
    
    // Test case 2: Zero time
    timespec ts2 = {0, 0};
    double ms2 = timespec_to_ms(ts2);
    print_timespec("Input", ts2);
    std::cout << "Output: " << ms2 << " microseconds (expected: 0)" << std::endl;
    
    // Test case 3: Negative time (-2.7 seconds normalized as -3, 300000000)
    timespec ts3 = {-3, 300000000};
    double ms3 = timespec_to_ms(ts3);
    print_timespec("Input", ts3);
    std::cout << "Output: " << ms3 << " microseconds (expected: -2700000)" << std::endl;
    
    // Test case 4: One second exactly
    timespec ts4 = {1, 0};
    double ms4 = timespec_to_ms(ts4);
    print_timespec("Input", ts4);
    std::cout << "Output: " << ms4 << " microseconds (expected: 1000000)" << std::endl;
}

void test_timespec_from_ms() {
    std::cout << "\n=== Testing timespec_from_ms ===" << std::endl;
    
    // Test case 1: Positive milliseconds (2.7 seconds = 2700000 microseconds)
    double ms1 = 2700000;
    timespec ts1 = timespec_from_ms(ms1);
    std::cout << "Input: " << ms1 << " microseconds" << std::endl;
    print_timespec("Output", ts1);
    std::cout << "Normalized: " << (is_normalized(ts1) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 2, tv_nsec = 700000000" << std::endl;
    
    // Test case 2: Zero
    double ms2 = 0;
    timespec ts2 = timespec_from_ms(ms2);
    std::cout << "\nInput: " << ms2 << " microseconds" << std::endl;
    print_timespec("Output", ts2);
    std::cout << "Normalized: " << (is_normalized(ts2) ? "YES" : "NO") << std::endl;
    
    // Test case 3: Negative milliseconds (-2.7 seconds = -2700000 microseconds)
    double ms3 = -2700000;
    timespec ts3 = timespec_from_ms(ms3);
    std::cout << "\nInput: " << ms3 << " microseconds" << std::endl;
    print_timespec("Output", ts3);
    std::cout << "Normalized: " << (is_normalized(ts3) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = -3, tv_nsec = 300000000" << std::endl;
    
    // Test case 4: Exactly one second
    double ms4 = 1000000;
    timespec ts4 = timespec_from_ms(ms4);
    std::cout << "\nInput: " << ms4 << " microseconds" << std::endl;
    print_timespec("Output", ts4);
    std::cout << "Normalized: " << (is_normalized(ts4) ? "YES" : "NO") << std::endl;
}

void test_timespec_now() {
    std::cout << "\n=== Testing timespec_now ===" << std::endl;
    
    timespec ts1 = timespec_now();
    print_timespec("Current time 1", ts1);
    std::cout << "Normalized: " << (is_normalized(ts1) ? "YES" : "NO") << std::endl;
    
    // Small delay
    for(volatile int i = 0; i < 1000000; i++);
    
    timespec ts2 = timespec_now();
    print_timespec("Current time 2", ts2);
    std::cout << "Time advanced: " << (ts2.tv_sec > ts1.tv_sec || 
                                       (ts2.tv_sec == ts1.tv_sec && ts2.tv_nsec > ts1.tv_nsec) ? 
                                       "YES" : "NO") << std::endl;
}

void test_timespec_negate() {
    std::cout << "\n=== Testing timespec_negate ===" << std::endl;
    
    // Test case 1: Positive time (2.7 seconds)
    timespec ts1 = {2, 700000000};
    timespec neg1 = timespec_negate(ts1);
    print_timespec("Input", ts1);
    print_timespec("Negated", neg1);
    std::cout << "Normalized: " << (is_normalized(neg1) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = -3, tv_nsec = 300000000" << std::endl;
    
    // Test case 2: Zero
    timespec ts2 = {0, 0};
    timespec neg2 = timespec_negate(ts2);
    std::cout << "\nInput: ";
    print_timespec("", ts2);
    print_timespec("Negated", neg2);
    std::cout << "Normalized: " << (is_normalized(neg2) ? "YES" : "NO") << std::endl;
    
    // Test case 3: Negative time (-2.7 seconds as -3, 300000000)
    timespec ts3 = {-3, 300000000};
    timespec neg3 = timespec_negate(ts3);
    print_timespec("\nInput", ts3);
    print_timespec("Negated", neg3);
    std::cout << "Normalized: " << (is_normalized(neg3) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 2, tv_nsec = 700000000" << std::endl;
    
    // Test case 4: Exactly one second
    timespec ts4 = {1, 0};
    timespec neg4 = timespec_negate(ts4);
    print_timespec("\nInput", ts4);
    print_timespec("Negated", neg4);
    std::cout << "Normalized: " << (is_normalized(neg4) ? "YES" : "NO") << std::endl;
}

void test_timespec_add() {
    std::cout << "\n=== Testing timespec_add ===" << std::endl;
    
    // Test case 1: Two positive times
    timespec ts1a = {2, 700000000};
    timespec ts1b = {1, 500000000};
    timespec sum1 = timespec_add(ts1a, ts1b);
    print_timespec("Time 1", ts1a);
    print_timespec("Time 2", ts1b);
    print_timespec("Sum", sum1);
    std::cout << "Normalized: " << (is_normalized(sum1) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 4, tv_nsec = 200000000" << std::endl;
    
    // Test case 2: Positive + zero
    timespec ts2a = {5, 123456789};
    timespec ts2b = {0, 0};
    timespec sum2 = timespec_add(ts2a, ts2b);
    print_timespec("\nTime 1", ts2a);
    print_timespec("Time 2", ts2b);
    print_timespec("Sum", sum2);
    std::cout << "Normalized: " << (is_normalized(sum2) ? "YES" : "NO") << std::endl;
    
    // Test case 3: Overflow nanoseconds
    timespec ts3a = {1, 600000000};
    timespec ts3b = {1, 600000000};
    timespec sum3 = timespec_add(ts3a, ts3b);
    print_timespec("\nTime 1", ts3a);
    print_timespec("Time 2", ts3b);
    print_timespec("Sum", sum3);
    std::cout << "Normalized: " << (is_normalized(sum3) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 3, tv_nsec = 200000000" << std::endl;
    
    // Test case 4: Positive + Negative
    timespec ts4a = {5, 300000000};
    timespec ts4b = {-2, 700000000};
    timespec sum4 = timespec_add(ts4a, ts4b);
    print_timespec("\nTime 1", ts4a);
    print_timespec("Time 2", ts4b);
    print_timespec("Sum", sum4);
    std::cout << "Normalized: " << (is_normalized(sum4) ? "YES" : "NO") << std::endl;
}

void test_timespec_subtract() {
    std::cout << "\n=== Testing timespec_subtract ===" << std::endl;
    
    // Test case 1: Subtract smaller from larger
    timespec ts1a = {5, 800000000};
    timespec ts1b = {2, 300000000};
    timespec diff1 = timespec_subtract(ts1a, ts1b);
    print_timespec("Time 1", ts1a);
    print_timespec("Time 2", ts1b);
    print_timespec("Difference", diff1);
    std::cout << "Normalized: " << (is_normalized(diff1) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 3, tv_nsec = 500000000" << std::endl;
    
    // Test case 2: Subtract from zero
    timespec ts2a = {0, 0};
    timespec ts2b = {2, 500000000};
    timespec diff2 = timespec_subtract(ts2a, ts2b);
    print_timespec("\nTime 1", ts2a);
    print_timespec("Time 2", ts2b);
    print_timespec("Difference", diff2);
    std::cout << "Normalized: " << (is_normalized(diff2) ? "YES" : "NO") << std::endl;
    
    // Test case 3: Subtract with nanosecond borrow
    timespec ts3a = {5, 200000000};
    timespec ts3b = {2, 700000000};
    timespec diff3 = timespec_subtract(ts3a, ts3b);
    print_timespec("\nTime 1", ts3a);
    print_timespec("Time 2", ts3b);
    print_timespec("Difference", diff3);
    std::cout << "Normalized: " << (is_normalized(diff3) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 2, tv_nsec = 500000000" << std::endl;
    
    // Test case 4: Subtract same values
    timespec ts4a = {3, 450000000};
    timespec ts4b = {3, 450000000};
    timespec diff4 = timespec_subtract(ts4a, ts4b);
    print_timespec("\nTime 1", ts4a);
    print_timespec("Time 2", ts4b);
    print_timespec("Difference", diff4);
    std::cout << "Normalized: " << (is_normalized(diff4) ? "YES" : "NO") << std::endl;
}

void test_timespec_wait() {
    std::cout << "\n=== Testing timespec_now ===" << std::endl;
    
    timespec ts1 = timespec_now();
    print_timespec("Current time 1", ts1);
    std::cout << "Normalized: " << (is_normalized(ts1) ? "YES" : "NO") << std::endl;
    
    // Small delay
    timespec delay = {1, 0};
    timespec_wait(delay);
    
    timespec ts2 = timespec_now();
    print_timespec("Current time 2", ts2);
    std::cout << "Time advanced: " << (ts2.tv_sec > ts1.tv_sec || 
                                       (ts2.tv_sec == ts1.tv_sec && ts2.tv_nsec > ts1.tv_nsec) ? 
                                       "YES" : "NO") << std::endl;

    timespec sub = timespec_subtract(ts2, ts1);
    print_timespec("Time 1 minus time 2", sub);

}

void test_operator_unary_minus() {
    std::cout << "\n=== Testing operator- (unary minus) ===" << std::endl;
    
    // Test case 1: Positive time (2.7 seconds)
    timespec ts1 = {2, 700000000};
    timespec neg1 = -ts1;
    print_timespec("Input", ts1);
    print_timespec("Output (-ts)", neg1);
    std::cout << "Normalized: " << (is_normalized(neg1) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = -3, tv_nsec = 300000000" << std::endl;
    
    // Test case 2: Zero
    timespec ts2 = {0, 0};
    timespec neg2 = -ts2;
    print_timespec("\nInput", ts2);
    print_timespec("Output (-ts)", neg2);
    std::cout << "Normalized: " << (is_normalized(neg2) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 0, tv_nsec = 0" << std::endl;
    
    // Test case 3: Negative time (-2.7 seconds as -3, 300000000)
    timespec ts3 = {-3, 300000000};
    timespec neg3 = -ts3;
    print_timespec("\nInput", ts3);
    print_timespec("Output (-ts)", neg3);
    std::cout << "Normalized: " << (is_normalized(neg3) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 2, tv_nsec = 700000000" << std::endl;
    
    // Test case 4: Exactly one second
    timespec ts4 = {1, 0};
    timespec neg4 = -ts4;
    print_timespec("\nInput", ts4);
    print_timespec("Output (-ts)", neg4);
    std::cout << "Normalized: " << (is_normalized(neg4) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = -1, tv_nsec = 0" << std::endl;
    
    // Test case 5: Only nanoseconds
    timespec ts5 = {0, 500000000};
    timespec neg5 = -ts5;
    print_timespec("\nInput", ts5);
    print_timespec("Output (-ts)", neg5);
    std::cout << "Normalized: " << (is_normalized(neg5) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = -1, tv_nsec = 500000000" << std::endl;
}

void test_operator_plus() {
    std::cout << "\n=== Testing operator+ (addition) ===" << std::endl;
    
    // Test case 1: Two positive times
    timespec ts1a = {2, 700000000};
    timespec ts1b = {1, 500000000};
    timespec sum1 = ts1a + ts1b;
    print_timespec("Time 1", ts1a);
    print_timespec("Time 2", ts1b);
    print_timespec("Sum (ts1 + ts2)", sum1);
    std::cout << "Normalized: " << (is_normalized(sum1) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 4, tv_nsec = 200000000" << std::endl;
    
    // Test case 2: Addition with zero
    timespec ts2a = {5, 123456789};
    timespec ts2b = {0, 0};
    timespec sum2 = ts2a + ts2b;
    print_timespec("\nTime 1", ts2a);
    print_timespec("Time 2", ts2b);
    print_timespec("Sum (ts1 + ts2)", sum2);
    std::cout << "Normalized: " << (is_normalized(sum2) ? "YES" : "NO") << std::endl;
    
    // Test case 3: Overflow nanoseconds
    timespec ts3a = {1, 600000000};
    timespec ts3b = {1, 600000000};
    timespec sum3 = ts3a + ts3b;
    print_timespec("\nTime 1", ts3a);
    print_timespec("Time 2", ts3b);
    print_timespec("Sum (ts1 + ts2)", sum3);
    std::cout << "Normalized: " << (is_normalized(sum3) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 3, tv_nsec = 200000000" << std::endl;
    
    // Test case 4: Positive + Negative (result positive)
    timespec ts4a = {5, 300000000};
    timespec ts4b = {-2, 700000000};
    timespec sum4 = ts4a + ts4b;
    print_timespec("\nTime 1", ts4a);
    print_timespec("Time 2", ts4b);
    print_timespec("Sum (ts1 + ts2)", sum4);
    std::cout << "Normalized: " << (is_normalized(sum4) ? "YES" : "NO") << std::endl;
    
    // Test case 5: Positive + Negative (result negative)
    timespec ts5a = {2, 300000000};
    timespec ts5b = {-5, 700000000};
    timespec sum5 = ts5a + ts5b;
    print_timespec("\nTime 1", ts5a);
    print_timespec("Time 2", ts5b);
    print_timespec("Sum (ts1 + ts2)", sum5);
    std::cout << "Normalized: " << (is_normalized(sum5) ? "YES" : "NO") << std::endl;
}

void test_operator_minus() {
    std::cout << "\n=== Testing operator- (subtraction) ===" << std::endl;
    
    // Test case 1: Subtract smaller from larger
    timespec ts1a = {5, 800000000};
    timespec ts1b = {2, 300000000};
    timespec diff1 = ts1a - ts1b;
    print_timespec("Time 1", ts1a);
    print_timespec("Time 2", ts1b);
    print_timespec("Difference (ts1 - ts2)", diff1);
    std::cout << "Normalized: " << (is_normalized(diff1) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 3, tv_nsec = 500000000" << std::endl;
    
    // Test case 2: Subtract from zero (result negative)
    timespec ts2a = {0, 0};
    timespec ts2b = {2, 500000000};
    timespec diff2 = ts2a - ts2b;
    print_timespec("\nTime 1", ts2a);
    print_timespec("Time 2", ts2b);
    print_timespec("Difference (ts1 - ts2)", diff2);
    std::cout << "Normalized: " << (is_normalized(diff2) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = -3, tv_nsec = 500000000" << std::endl;
    
    // Test case 3: Subtract with nanosecond borrow
    timespec ts3a = {5, 200000000};
    timespec ts3b = {2, 700000000};
    timespec diff3 = ts3a - ts3b;
    print_timespec("\nTime 1", ts3a);
    print_timespec("Time 2", ts3b);
    print_timespec("Difference (ts1 - ts2)", diff3);
    std::cout << "Normalized: " << (is_normalized(diff3) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 2, tv_nsec = 500000000" << std::endl;
    
    // Test case 4: Subtract same values
    timespec ts4a = {3, 450000000};
    timespec ts4b = {3, 450000000};
    timespec diff4 = ts4a - ts4b;
    print_timespec("\nTime 1", ts4a);
    print_timespec("Time 2", ts4b);
    print_timespec("Difference (ts1 - ts2)", diff4);
    std::cout << "Normalized: " << (is_normalized(diff4) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 0, tv_nsec = 0" << std::endl;
    
    // Test case 5: Subtract larger from smaller (result negative)
    timespec ts5a = {2, 300000000};
    timespec ts5b = {5, 800000000};
    timespec diff5 = ts5a - ts5b;
    print_timespec("\nTime 1", ts5a);
    print_timespec("Time 2", ts5b);
    print_timespec("Difference (ts1 - ts2)", diff5);
    std::cout << "Normalized: " << (is_normalized(diff5) ? "YES" : "NO") << std::endl;
}

void test_operator_plus_equals() {
    std::cout << "\n=== Testing operator+= (addition assignment) ===" << std::endl;
    
    // Test case 1: Add positive to positive
    timespec ts1 = {2, 700000000};
    timespec add1 = {1, 500000000};
    print_timespec("Original", ts1);
    print_timespec("Adding", add1);
    ts1 += add1;
    print_timespec("After +=", ts1);
    std::cout << "Normalized: " << (is_normalized(ts1) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 4, tv_nsec = 200000000" << std::endl;
    
    // Test case 2: Add zero
    timespec ts2 = {5, 123456789};
    timespec add2 = {0, 0};
    print_timespec("\nOriginal", ts2);
    print_timespec("Adding", add2);
    ts2 += add2;
    print_timespec("After +=", ts2);
    std::cout << "Normalized: " << (is_normalized(ts2) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 5, tv_nsec = 123456789" << std::endl;
    
    // Test case 3: Overflow nanoseconds
    timespec ts3 = {1, 600000000};
    timespec add3 = {1, 600000000};
    print_timespec("\nOriginal", ts3);
    print_timespec("Adding", add3);
    ts3 += add3;
    print_timespec("After +=", ts3);
    std::cout << "Normalized: " << (is_normalized(ts3) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 3, tv_nsec = 200000000" << std::endl;
    
    // Test case 4: Chain operations
    timespec ts4 = {1, 0};
    timespec add4a = {1, 250000000};
    timespec add4b = {1, 250000000};
    print_timespec("\nOriginal", ts4);
    print_timespec("Adding first", add4a);
    print_timespec("Adding second", add4b);
    ts4 += add4a;
    ts4 += add4b;
    print_timespec("After chained +=", ts4);
    std::cout << "Normalized: " << (is_normalized(ts4) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 3, tv_nsec = 500000000" << std::endl;
}

void test_operator_minus_equals() {
    std::cout << "\n=== Testing operator-= (subtraction assignment) ===" << std::endl;
    
    // Test case 1: Subtract smaller from larger
    timespec ts1 = {5, 800000000};
    timespec sub1 = {2, 300000000};
    print_timespec("Original", ts1);
    print_timespec("Subtracting", sub1);
    ts1 -= sub1;
    print_timespec("After -=", ts1);
    std::cout << "Normalized: " << (is_normalized(ts1) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 3, tv_nsec = 500000000" << std::endl;
    
    // Test case 2: Subtract zero
    timespec ts2 = {5, 123456789};
    timespec sub2 = {0, 0};
    print_timespec("\nOriginal", ts2);
    print_timespec("Subtracting", sub2);
    ts2 -= sub2;
    print_timespec("After -=", ts2);
    std::cout << "Normalized: " << (is_normalized(ts2) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 5, tv_nsec = 123456789" << std::endl;
    
    // Test case 3: Subtract with nanosecond borrow
    timespec ts3 = {5, 200000000};
    timespec sub3 = {2, 700000000};
    print_timespec("\nOriginal", ts3);
    print_timespec("Subtracting", sub3);
    ts3 -= sub3;
    print_timespec("After -=", ts3);
    std::cout << "Normalized: " << (is_normalized(ts3) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 2, tv_nsec = 500000000" << std::endl;
    
    // Test case 4: Subtract to get negative result
    timespec ts4 = {2, 300000000};
    timespec sub4 = {5, 800000000};
    print_timespec("\nOriginal", ts4);
    print_timespec("Subtracting", sub4);
    ts4 -= sub4;
    print_timespec("After -=", ts4);
    std::cout << "Normalized: " << (is_normalized(ts4) ? "YES" : "NO") << std::endl;
    
    // Test case 5: Chain operations
    timespec ts5 = {10, 0};
    timespec sub5a = {2, 250000000};
    timespec sub5b = {3, 250000000};
    print_timespec("\nOriginal", ts5);
    print_timespec("Subtracting first", sub5a);
    print_timespec("Subtracting second", sub5b);
    ts5 -= sub5a;
    ts5 -= sub5b;
    print_timespec("After chained -=", ts5);
    std::cout << "Normalized: " << (is_normalized(ts5) ? "YES" : "NO") << std::endl;
    std::cout << "Expected: tv_sec = 4, tv_nsec = 500000000" << std::endl;
}

void test_operator_equality() {
    std::cout << "\n=== Testing operator== (equality) ===" << std::endl;
    
    // Test case 1: Equal times
    timespec ts1a = {2, 700000000};
    timespec ts1b = {2, 700000000};
    print_timespec("Time 1", ts1a);
    print_timespec("Time 2", ts1b);
    std::cout << "ts1 == ts2: " << (ts1a == ts1b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
    
    // Test case 2: Different seconds
    timespec ts2a = {2, 700000000};
    timespec ts2b = {3, 700000000};
    print_timespec("\nTime 1", ts2a);
    print_timespec("Time 2", ts2b);
    std::cout << "ts1 == ts2: " << (ts2a == ts2b ? "TRUE" : "FALSE") << " (expected: FALSE)" << std::endl;
    
    // Test case 3: Different nanoseconds
    timespec ts3a = {2, 700000000};
    timespec ts3b = {2, 800000000};
    print_timespec("\nTime 1", ts3a);
    print_timespec("Time 2", ts3b);
    std::cout << "ts1 == ts2: " << (ts3a == ts3b ? "TRUE" : "FALSE") << " (expected: FALSE)" << std::endl;
    
    // Test case 4: Both zero
    timespec ts4a = {0, 0};
    timespec ts4b = {0, 0};
    print_timespec("\nTime 1", ts4a);
    print_timespec("Time 2", ts4b);
    std::cout << "ts1 == ts2: " << (ts4a == ts4b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
    
    // Test case 5: Negative times equal
    timespec ts5a = {-3, 300000000};
    timespec ts5b = {-3, 300000000};
    print_timespec("\nTime 1", ts5a);
    print_timespec("Time 2", ts5b);
    std::cout << "ts1 == ts2: " << (ts5a == ts5b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
}

void test_operator_inequality() {
    std::cout << "\n=== Testing operator!= (inequality) ===" << std::endl;
    
    // Test case 1: Equal times
    timespec ts1a = {2, 700000000};
    timespec ts1b = {2, 700000000};
    print_timespec("Time 1", ts1a);
    print_timespec("Time 2", ts1b);
    std::cout << "ts1 != ts2: " << (ts1a != ts1b ? "TRUE" : "FALSE") << " (expected: FALSE)" << std::endl;
    
    // Test case 2: Different seconds
    timespec ts2a = {2, 700000000};
    timespec ts2b = {3, 700000000};
    print_timespec("\nTime 1", ts2a);
    print_timespec("Time 2", ts2b);
    std::cout << "ts1 != ts2: " << (ts2a != ts2b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
    
    // Test case 3: Different nanoseconds
    timespec ts3a = {2, 700000000};
    timespec ts3b = {2, 800000000};
    print_timespec("\nTime 1", ts3a);
    print_timespec("Time 2", ts3b);
    std::cout << "ts1 != ts2: " << (ts3a != ts3b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
    
    // Test case 4: Both zero
    timespec ts4a = {0, 0};
    timespec ts4b = {0, 0};
    print_timespec("\nTime 1", ts4a);
    print_timespec("Time 2", ts4b);
    std::cout << "ts1 != ts2: " << (ts4a != ts4b ? "TRUE" : "FALSE") << " (expected: FALSE)" << std::endl;
}

void test_operator_less_than() {
    std::cout << "\n=== Testing operator< (less than) ===" << std::endl;
    
    // Test case 1: ts1 < ts2 (seconds differ)
    timespec ts1a = {2, 700000000};
    timespec ts1b = {3, 700000000};
    print_timespec("Time 1", ts1a);
    print_timespec("Time 2", ts1b);
    std::cout << "ts1 < ts2: " << (ts1a < ts1b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
    
    // Test case 2: ts1 > ts2 (seconds differ)
    timespec ts2a = {5, 700000000};
    timespec ts2b = {3, 700000000};
    print_timespec("\nTime 1", ts2a);
    print_timespec("Time 2", ts2b);
    std::cout << "ts1 < ts2: " << (ts2a < ts2b ? "TRUE" : "FALSE") << " (expected: FALSE)" << std::endl;
    
    // Test case 3: ts1 < ts2 (nanoseconds differ)
    timespec ts3a = {2, 700000000};
    timespec ts3b = {2, 800000000};
    print_timespec("\nTime 1", ts3a);
    print_timespec("Time 2", ts3b);
    std::cout << "ts1 < ts2: " << (ts3a < ts3b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
    
    // Test case 4: Equal times
    timespec ts4a = {2, 700000000};
    timespec ts4b = {2, 700000000};
    print_timespec("\nTime 1", ts4a);
    print_timespec("Time 2", ts4b);
    std::cout << "ts1 < ts2: " << (ts4a < ts4b ? "TRUE" : "FALSE") << " (expected: FALSE)" << std::endl;
    
    // Test case 5: Negative vs positive
    timespec ts5a = {-1, 500000000};
    timespec ts5b = {1, 500000000};
    print_timespec("\nTime 1", ts5a);
    print_timespec("Time 2", ts5b);
    std::cout << "ts1 < ts2: " << (ts5a < ts5b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
    
    // Test case 6: Both negative
    timespec ts6a = {-3, 300000000};
    timespec ts6b = {-2, 700000000};
    print_timespec("\nTime 1", ts6a);
    print_timespec("Time 2", ts6b);
    std::cout << "ts1 < ts2: " << (ts6a < ts6b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
}

void test_operator_greater_than() {
    std::cout << "\n=== Testing operator> (greater than) ===" << std::endl;
    
    // Test case 1: ts1 > ts2 (seconds differ)
    timespec ts1a = {5, 700000000};
    timespec ts1b = {3, 700000000};
    print_timespec("Time 1", ts1a);
    print_timespec("Time 2", ts1b);
    std::cout << "ts1 > ts2: " << (ts1a > ts1b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
    
    // Test case 2: ts1 < ts2 (seconds differ)
    timespec ts2a = {2, 700000000};
    timespec ts2b = {3, 700000000};
    print_timespec("\nTime 1", ts2a);
    print_timespec("Time 2", ts2b);
    std::cout << "ts1 > ts2: " << (ts2a > ts2b ? "TRUE" : "FALSE") << " (expected: FALSE)" << std::endl;
    
    // Test case 3: ts1 > ts2 (nanoseconds differ)
    timespec ts3a = {2, 800000000};
    timespec ts3b = {2, 700000000};
    print_timespec("\nTime 1", ts3a);
    print_timespec("Time 2", ts3b);
    std::cout << "ts1 > ts2: " << (ts3a > ts3b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
    
    // Test case 4: Equal times
    timespec ts4a = {2, 700000000};
    timespec ts4b = {2, 700000000};
    print_timespec("\nTime 1", ts4a);
    print_timespec("Time 2", ts4b);
    std::cout << "ts1 > ts2: " << (ts4a > ts4b ? "TRUE" : "FALSE") << " (expected: FALSE)" << std::endl;
    
    // Test case 5: Positive vs negative
    timespec ts5a = {1, 500000000};
    timespec ts5b = {-1, 500000000};
    print_timespec("\nTime 1", ts5a);
    print_timespec("Time 2", ts5b);
    std::cout << "ts1 > ts2: " << (ts5a > ts5b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
    
    // Test case 6: Both negative
    timespec ts6a = {-2, 700000000};
    timespec ts6b = {-3, 300000000};
    print_timespec("\nTime 1", ts6a);
    print_timespec("Time 2", ts6b);
    std::cout << "ts1 > ts2: " << (ts6a > ts6b ? "TRUE" : "FALSE") << " (expected: TRUE)" << std::endl;
}

int main() {
    std::cout << "======================================" << std::endl;
    std::cout << "  TIMESPEC FUNCTIONS TEST SUITE" << std::endl;
    std::cout << "======================================" << std::endl;
    
    test_timespec_to_ms();
    test_timespec_from_ms();
    test_timespec_now();
    test_timespec_negate();
    test_timespec_add();
    test_timespec_subtract();
    test_timespec_wait();

    std::cout << "\n\n======================================" << std::endl;
    std::cout << "  TIMESPEC OPERATORS TEST SUITE" << std::endl;
    std::cout << "======================================" << std::endl;
    
    // Test operators
    test_operator_unary_minus();
    test_operator_plus();
    test_operator_minus();
    test_operator_plus_equals();
    test_operator_minus_equals();
    test_operator_equality();
    test_operator_inequality();
    test_operator_less_than();
    test_operator_greater_than();

    std::cout << "\n======================================" << std::endl;
    std::cout << "  ALL TESTS COMPLETED" << std::endl;
    std::cout << "======================================" << std::endl;
    
    return 0;
}
