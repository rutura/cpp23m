#include "utilities.h"
#include <fmt/format.h>
#include <limits>

void number_systems(){
    //Integers and number systems
    int number1 =  15; // Decimal
    int number2 = 017;  // Octal
    int number3 = 0x0F; // Hexadecimal
    int number4 = 0b00001111;   // Binary

    fmt::println("number1: {}", number1);
    fmt::println("number2: {}", number2);
    fmt::println("number3: {}", number3);
    fmt::println("number4: {}", number4);
}

void floating_point_types(){
    // Floating point types
    // floats offer 7 digits of precision while double offers 15 digits of precision.
    // long double offers 18 digits of precision
    // The range of float is 1.17549e-38 to 3.40282e+38 
    //The range of double is 2.22507e-308 to 1.79769e+308
    //The range of long double is 3.3621e-4932 to 1.18973e+4932

    //Single precision (float)
    float single_precision = 1.123456789123456789f;

    //Double precision (double)
    double double_precision = 1.123456789123456789;

    //Extended precision (long double)
    long double long_double_precision = 1.123456789123456789123456789L;

    //Print results with 30 decimal places for comparison
    fmt::println("Float (single precision): {:.30f}", single_precision);
    fmt::println("Double (double precision): {:.30f}", double_precision);
    fmt::println("Long double (extended precision): {:.30Lf}", long_double_precision);

    fmt::println("Size of float: {} bytes", sizeof(float));
    fmt::println("Size of double: {} bytes", sizeof(double));
    fmt::println("Size of long double: {} bytes", sizeof(long double));
}

void numeric_limits(){
    fmt::println("The range for int is from {} to {}", 
                                    std::numeric_limits<int>::min(),
                                    std::numeric_limits<int>::max());
    fmt::println("The range for float is from {} to {}", 
                                    std::numeric_limits<float>::min(),
                                    std::numeric_limits<float>::max());

    fmt::println("The range for double is from {} to {}", 
                                    std::numeric_limits<double>::min(),
                                    std::numeric_limits<double>::max());

    fmt::println("The range for long double is from {} to {}", 
                                    std::numeric_limits<long double>::min(),
                                    std::numeric_limits<long double>::max());
}
