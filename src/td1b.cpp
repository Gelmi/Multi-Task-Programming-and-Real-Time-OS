#include "chrono.h"
#include "timespec.h"
#include <iostream>
#include <iomanip>
#include <cmath>

// Helper function to print a timespec value
void print_timespec(const std::string& label, const timespec& ts) {
    std::cout << label << ": tv_sec = " << ts.tv_sec 
              << ", tv_nsec = " << ts.tv_nsec << std::endl;
}

// Helper function to check if a value is within an acceptable range
bool is_within_tolerance(double actual, double expected, double tolerance_percent = 10.0) {
    double tolerance = expected * (tolerance_percent / 100.0);
    return std::abs(actual - expected) <= tolerance;
}

void test_chrono_constructor() {
    std::cout << "\n=== Testing Chrono Constructor ===" << std::endl;
    
    Chrono chrono;
    std::cout << "Chrono object created" << std::endl;
    std::cout << "isActive(): " << (chrono.isActive() ? "TRUE" : "FALSE") 
              << " (expected: TRUE)" << std::endl;
    
    // The chrono should start immediately upon construction
    timespec lap1 = chrono.lap();
    print_timespec("Initial lap", lap1);
    std::cout << "Lap should be very close to zero (some nanoseconds)" << std::endl;
}

void test_chrono_restart() {
    std::cout << "\n=== Testing Chrono restart() ===" << std::endl;
    
    Chrono chrono;
    std::cout << "Chrono created and started" << std::endl;
    
    // Wait a bit
    timespec delay1 = {0, 100000000}; // 100ms
    std::cout << "Waiting 100ms..." << std::endl;
    timespec_wait(delay1);
    
    double lap1_ms = chrono.lap_ms();
    std::cout << "Lap after wait: " << lap1_ms << " microseconds" << std::endl;
    
    // Restart the chrono
    std::cout << "\nRestarting chrono..." << std::endl;
    chrono.restart();
    
    double lap2_ms = chrono.lap_ms();
    std::cout << "Lap immediately after restart: " << lap2_ms << " microseconds" << std::endl;
    std::cout << "Should be close to 0 (less than lap1)" << std::endl;
    std::cout << "lap2 < lap1: " << (lap2_ms < lap1_ms ? "TRUE" : "FALSE") 
              << " (expected: TRUE)" << std::endl;
}

void test_chrono_lap_active() {
    std::cout << "\n=== Testing Chrono lap() while active ===" << std::endl;
    
    Chrono chrono;
    std::cout << "Chrono started" << std::endl;
    std::cout << "isActive(): " << (chrono.isActive() ? "TRUE" : "FALSE") 
              << " (expected: TRUE)" << std::endl;
    
    // Take multiple laps while active
    for (int i = 1; i <= 3; i++) {
        timespec delay = {0, 50000000}; // 50ms
        std::cout << "\nWaiting 50ms (iteration " << i << ")..." << std::endl;
        timespec_wait(delay);
        
        timespec lap = chrono.lap();
        double lap_ms = chrono.lap_ms();
        print_timespec("Lap timespec", lap);
        std::cout << "Lap in microseconds: " << lap_ms << std::endl;
        std::cout << "Expected approximately: " << (i * 50000) << " microseconds" << std::endl;
        
        bool in_range = is_within_tolerance(lap_ms, i * 50000.0, 15.0);
        std::cout << "Within tolerance: " << (in_range ? "YES" : "NO") << std::endl;
    }
    
    std::cout << "\nChrono still active: " << (chrono.isActive() ? "TRUE" : "FALSE") 
              << " (expected: TRUE)" << std::endl;
}

void test_chrono_stop() {
    std::cout << "\n=== Testing Chrono stop() ===" << std::endl;
    
    Chrono chrono;
    std::cout << "Chrono started" << std::endl;
    
    // Wait before stopping
    timespec delay = {0, 150000000}; // 150ms
    std::cout << "Waiting 150ms..." << std::endl;
    timespec_wait(delay);
    
    std::cout << "\nStopping chrono..." << std::endl;
    timespec stop_time = chrono.stop();
    print_timespec("Stop time returned", stop_time);
    
    std::cout << "\nisActive() after stop: " << (chrono.isActive() ? "TRUE" : "FALSE") 
              << " (expected: FALSE)" << std::endl;
    
    // Get lap immediately after stopping
    double lap1_ms = chrono.lap_ms();
    std::cout << "\nLap immediately after stop: " << lap1_ms << " microseconds" << std::endl;
    std::cout << "Expected approximately: 150000 microseconds" << std::endl;
    
    // Wait some more time
    std::cout << "\nWaiting additional 100ms..." << std::endl;
    timespec delay2 = {0, 100000000}; // 100ms
    timespec_wait(delay2);
    
    // Lap should remain the same since chrono is stopped
    double lap2_ms = chrono.lap_ms();
    std::cout << "Lap after additional wait: " << lap2_ms << " microseconds" << std::endl;
    std::cout << "Should be same as previous lap (chrono is stopped)" << std::endl;
    std::cout << "lap2 == lap1: " << (std::abs(lap2_ms - lap1_ms) < 1.0 ? "TRUE" : "FALSE") 
              << " (expected: TRUE)" << std::endl;
}

void test_chrono_lap_stopped() {
    std::cout << "\n=== Testing Chrono lap() after stopped ===" << std::endl;
    
    Chrono chrono;
    std::cout << "Chrono started" << std::endl;
    
    // Wait and stop
    timespec delay1 = {0, 200000000}; // 200ms
    std::cout << "Waiting 200ms..." << std::endl;
    timespec_wait(delay1);
    
    chrono.stop();
    std::cout << "Chrono stopped" << std::endl;
    
    double stopped_lap_ms = chrono.lap_ms();
    std::cout << "Lap when stopped: " << stopped_lap_ms << " microseconds" << std::endl;
    
    // Wait more time
    std::cout << "\nWaiting additional 150ms..." << std::endl;
    timespec delay2 = {0, 150000000}; // 150ms
    timespec_wait(delay2);
    
    double final_lap_ms = chrono.lap_ms();
    std::cout << "Lap after wait (still stopped): " << final_lap_ms << " microseconds" << std::endl;
    std::cout << "Difference from stopped lap: " << std::abs(final_lap_ms - stopped_lap_ms) 
              << " microseconds" << std::endl;
    std::cout << "Should be essentially the same (< 1 microsecond difference)" << std::endl;
}

void test_chrono_restart_after_stop() {
    std::cout << "\n=== Testing Chrono restart() after stop() ===" << std::endl;
    
    Chrono chrono;
    std::cout << "Chrono started" << std::endl;
    
    // Wait and stop
    timespec delay1 = {0, 100000000}; // 100ms
    std::cout << "Waiting 100ms..." << std::endl;
    timespec_wait(delay1);
    
    chrono.stop();
    std::cout << "Chrono stopped" << std::endl;
    double stopped_lap_ms = chrono.lap_ms();
    std::cout << "Lap when stopped: " << stopped_lap_ms << " microseconds" << std::endl;
    
    // Restart
    std::cout << "\nRestarting chrono..." << std::endl;
    chrono.restart();
    std::cout << "isActive() after restart: " << (chrono.isActive() ? "TRUE" : "FALSE") 
              << " (expected: TRUE)" << std::endl;
    
    double restart_lap_ms = chrono.lap_ms();
    std::cout << "Lap immediately after restart: " << restart_lap_ms << " microseconds" << std::endl;
    std::cout << "Should be close to 0" << std::endl;
    
    // Wait and check again
    std::cout << "\nWaiting 80ms..." << std::endl;
    timespec delay2 = {0, 80000000}; // 80ms
    timespec_wait(delay2);
    
    double new_lap_ms = chrono.lap_ms();
    std::cout << "Lap after wait: " << new_lap_ms << " microseconds" << std::endl;
    std::cout << "Expected approximately: 80000 microseconds" << std::endl;
    
    bool in_range = is_within_tolerance(new_lap_ms, 80000.0, 15.0);
    std::cout << "Within tolerance: " << (in_range ? "YES" : "NO") << std::endl;
}

void test_chrono_multiple_stops() {
    std::cout << "\n=== Testing Multiple stop() calls ===" << std::endl;
    
    Chrono chrono;
    std::cout << "Chrono started" << std::endl;
    
    // Wait and stop first time
    timespec delay1 = {0, 100000000}; // 100ms
    std::cout << "Waiting 100ms..." << std::endl;
    timespec_wait(delay1);
    
    timespec stop1 = chrono.stop();
    std::cout << "First stop()" << std::endl;
    print_timespec("Stop time 1", stop1);
    
    // Wait and stop again
    std::cout << "\nWaiting 50ms..." << std::endl;
    timespec delay2 = {0, 50000000}; // 50ms
    timespec_wait(delay2);
    
    timespec stop2 = chrono.stop();
    std::cout << "Second stop()" << std::endl;
    print_timespec("Stop time 2", stop2);
    
    std::cout << "\nNote: Second stop updates the stop time even though chrono was already stopped" << std::endl;
    std::cout << "stop2 > stop1: " << (stop2.tv_sec > stop1.tv_sec || 
                                       (stop2.tv_sec == stop1.tv_sec && stop2.tv_nsec > stop1.tv_nsec) 
                                       ? "TRUE" : "FALSE") << std::endl;
}

void test_chrono_precision() {
    std::cout << "\n=== Testing Chrono Precision ===" << std::endl;
    
    Chrono chrono;
    std::cout << "Testing various short delays for precision" << std::endl;
    
    struct TestCase {
        long nanoseconds;
        const char* description;
    };
    
    TestCase tests[] = {
        {10000000, "10ms"},
        {50000000, "50ms"},
        {100000000, "100ms"},
        {250000000, "250ms"},
        {500000000, "500ms"}
    };
    
    for (const auto& test : tests) {
        chrono.restart();
        
        timespec delay = {0, test.nanoseconds};
        std::cout << "\nWaiting " << test.description << "..." << std::endl;
        timespec_wait(delay);
        
        double lap_ms = chrono.lap_ms();
        double expected_us = test.nanoseconds / 1000.0;
        
        std::cout << "Measured: " << lap_ms << " microseconds" << std::endl;
        std::cout << "Expected: " << expected_us << " microseconds" << std::endl;
        std::cout << "Difference: " << std::abs(lap_ms - expected_us) << " microseconds" << std::endl;
        
        bool in_range = is_within_tolerance(lap_ms, expected_us, 15.0);
        std::cout << "Within 15% tolerance: " << (in_range ? "YES" : "NO") << std::endl;
    }
}

void test_chrono_long_duration() {
    std::cout << "\n=== Testing Chrono with Longer Duration ===" << std::endl;
    
    Chrono chrono;
    std::cout << "Chrono started" << std::endl;
    
    // Wait for 1 second (1000ms)
    timespec delay = {1, 0}; // 1 second
    std::cout << "Waiting 1 second..." << std::endl;
    timespec_wait(delay);
    
    double lap_ms = chrono.lap_ms();
    std::cout << "Lap after 1 second: " << lap_ms << " microseconds" << std::endl;
    std::cout << "Expected: 1000000 microseconds" << std::endl;
    
    bool in_range = is_within_tolerance(lap_ms, 1000000.0, 5.0);
    std::cout << "Within 5% tolerance: " << (in_range ? "YES" : "NO") << std::endl;
    
    timespec lap_ts = chrono.lap();
    print_timespec("Lap as timespec", lap_ts);
}

void test_chrono_edge_cases() {
    std::cout << "\n=== Testing Chrono Edge Cases ===" << std::endl;
    
    // Test 1: Immediate lap
    std::cout << "\nTest 1: Immediate lap after creation" << std::endl;
    Chrono chrono1;
    double immediate_lap = chrono1.lap_ms();
    std::cout << "Immediate lap: " << immediate_lap << " microseconds" << std::endl;
    std::cout << "Should be very close to 0 (< 1000 microseconds)" << std::endl;
    std::cout << "Result: " << (immediate_lap < 1000 ? "PASS" : "FAIL") << std::endl;
    
    // Test 2: Multiple laps without stopping
    std::cout << "\nTest 2: Multiple consecutive laps (active)" << std::endl;
    Chrono chrono2;
    double last_lap = 0;
    for (int i = 0; i < 3; i++) {
        timespec delay = {0, 30000000}; // 30ms
        timespec_wait(delay);
        double current_lap = chrono2.lap_ms();
        std::cout << "Lap " << (i+1) << ": " << current_lap << " microseconds" 
                  << " (should be > previous)" << std::endl;
        if (i > 0) {
            std::cout << "  current > previous: " << (current_lap > last_lap ? "TRUE" : "FALSE") << std::endl;
        }
        last_lap = current_lap;
    }
    
    // Test 3: Restart multiple times
    std::cout << "\nTest 3: Multiple restarts" << std::endl;
    Chrono chrono3;
    for (int i = 0; i < 3; i++) {
        timespec delay = {0, 25000000}; // 25ms
        timespec_wait(delay);
        double lap_before = chrono3.lap_ms();
        chrono3.restart();
        double lap_after = chrono3.lap_ms();
        std::cout << "Restart " << (i+1) << ": lap before = " << lap_before 
                  << " us, lap after = " << lap_after << " us" << std::endl;
        std::cout << "  lap_after < lap_before: " << (lap_after < lap_before ? "TRUE" : "FALSE") << std::endl;
    }
}

int main() {
    std::cout << "======================================" << std::endl;
    std::cout << "    CHRONO CLASS TEST SUITE" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << "\nNote: Timing tests may show some variance due to" << std::endl;
    std::cout << "system scheduling and other factors." << std::endl;
    
    test_chrono_constructor();
    test_chrono_restart();
    test_chrono_lap_active();
    test_chrono_stop();
    test_chrono_lap_stopped();
    test_chrono_restart_after_stop();
    test_chrono_multiple_stops();
    test_chrono_precision();
    test_chrono_long_duration();
    test_chrono_edge_cases();
    
    std::cout << "\n======================================" << std::endl;
    std::cout << "     ALL CHRONO TESTS COMPLETED" << std::endl;
    std::cout << "======================================" << std::endl;
    
    return 0;
}
