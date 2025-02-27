#pragma once

#include <array>
#include <fmt/format.h>

void setup_and_visit(){
    std::array<int,5> arr {1, 2, 3, 4, 5};

    //Access the elements using the [] syntax
    /*
    for(size_t i{0}; i < arr.size(); ++i){
        fmt::println("arr[{}]: {}", i, arr[100]);
    }
    */

    //Use range based for loop
    /*
    for (const auto element : arr) {
        fmt::println("{} ", element);
    }
    */
    
    //Access the elements using the [] syntax
    for(size_t i{0}; i < arr.size(); ++i){
        fmt::println("arr[{}]: {}", i, arr.at(i));
    }
}


void modifications(){
    //Modifying elements
    std::array<int,5> arr {1, 2, 3, 4, 5};

    //Modify
    arr[0] = 100;
    arr.at(1) = 200;

    //Print the array
    for (size_t i = 0; i < arr.size(); ++i) {
        fmt::println("arr[{}] = {}", i, arr[i]);
    }
}


void fill_with_data(){
    //Filling an array with a value
	std::array<int, 5> arr; // Array initialized with junk values

    // Filling array with a single value
    arr.fill(7);

    for (const auto element : arr) {
        fmt::println("{} ", element);
    }
}


void front_and_back(){
    //Front and back functions
    std::array<int, 5> arr {1, 2, 3, 4, 5};
    fmt::println("First element: {}", arr.front());
    fmt::println("Last element: {}", arr.back());
}


void two_dimensional_data(){

    //Multi-dimensional data
    std::array< std::array<int, 2>, 3> arr = {
        {
            {1, 2},
            {3, 4},
            {5, 6}
        }
    };

    //2D loop
    for(const auto row: arr){
        for(const auto element: row){
            fmt::println("{}", element);
        }
    }
}


void comparing_std_array(){
    //7. Comparing arrays
	std::array<int, 3> arr1 = {1, 2, 3};
    std::array<int, 3> arr2 = {1, 2, 3};
    std::array<int, 3> arr3 = {1, 2, 4};
    std::array<int, 3> arr4 = {0, 2, 3};

    // Comparing arrays for equality
    if (arr1 == arr2) {
        fmt::println("arr1 is equal to arr2");
    } else {
        fmt::println("arr1 is not equal to arr2");
    }

    // Comparing arrays for inequality
    if (arr1 != arr3) {
        fmt::println("arr1 is not equal to arr3");
    } else {
        fmt::println("arr1 is equal to arr3");
    }
    // Lexicographical comparison
    if (arr1 < arr3) {
        fmt::println("arr1 is less than arr3");
    } else {
        fmt::println("arr1 is not less than arr3");
    }

    if (arr1 <= arr2) {
        fmt::println("arr1 is less than or equal to arr2");
    } else {
        fmt::println("arr1 is not less than or equal to arr2");
    }

    if (arr3 > arr4) {
        fmt::println("arr3 is greater than arr4");
    } else {
        fmt::println("arr3 is not greater than arr4");
    }

    if (arr3 >= arr1) {
        fmt::println("arr3 is greater than or equal to arr1");
    } else {
        fmt::println("arr3 is not greater than or equal to arr1");
    }
}


void assigning_std_array(){
    //Assigning one array to another
    std::array<int, 5> arr1 = {1, 2, 3, 4, 5};
    std::array<int, 5> arr2 = {6, 7, 8, 9, 10};

    // Printing original arrays
    fmt::println("Original arr1: ");
    for (const auto& element : arr1) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");

    fmt::println("Original arr2: ");
    for (const auto& element : arr2) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");

    // Assigning arr2 to arr1
    arr1 = arr2;

    // Printing arrays after assignment
    fmt::println("arr1 after assignment: ");
    for (const auto& element : arr1) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");

    fmt::println("arr2 after assignment: ");
    for (const auto& element : arr2) {
        fmt::print("{} ", element);
    }
    fmt::print("\n");
}
