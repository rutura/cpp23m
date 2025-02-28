#pragma once

#include <fmt/format.h>
#include <iostream>
#include "overloading_1.h"
#include "overloading_2.h"
#include "overloading_4.h"

inline void overloading_1_demo(){
    using namespace overloading_1;
    print(10);
    print(10,20);
    print(3.14);
    print("Hello World!");
}

inline void overloading_2_demo(){
    using namespace overloading_2;
    int array[] = {1, 2, 3, 4, 5};
    process(array, 5);  // Calls the array version
    process(42);        // Calls the single value version   
}

/*
    . Overloading std::getline
    . std::getline is overloaded in the C++ standard library to allow reading a whole line or reading up to a specific delimiter.
    . These are examples I picked up for this lecture, but the exhaustive list of overloads should be checked in the standard library documentation.
*/
inline void overloading_3_demo(){
  std::string line;

  // Read a whole line from standard input
  fmt::print("Enter a line: ");
  std::getline(std::cin, line);
  fmt::println("You entered: {}", line);

  // Read up to a specific delimiter (comma)
  fmt::print("Enter values separated by commas: ");
  std::getline(std::cin, line, ',');
  fmt::println("First value: {}", line);  
}

inline void overloading_4_demo(){
    using namespace overloading_4;
    fmt::print("Rolling a 6-sided die: {}\n", roll());
    fmt::print("Rolling a 20-sided die: {}\n", roll(20));
    fmt::print("Rolling 3 6-sided dice: {}\n", roll(6, 3));

    fmt::print("Area of a square with side 2.0: {}\n", area(2.0));
    fmt::print("Area of a rectangle with length 2.0 and width 3.0: {}\n", area(2.0, 3.0));
    fmt::print("Area of a circle with radius 1.0: {}\n", area(1.0, true));

    respond();
    respond("What is the meaning of life?");
    respond("What is the meaning of life?", true);
}
