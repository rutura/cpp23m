/*
/*
    . constexpr and consteval functions
        . constexpr function: 
            . Can be evaluated at compile time or runtime, depending on how it is used. If all inputs are constant expressions, it is evaluated at compile time; otherwise, it is evaluated at runtime.

        . consteval function: 
            . Must be evaluated only at compile time. If called in a context that cannot guarantee compile-time evaluation, it results in a compilation error.
        
*/
#include <fmt/format.h>
#include "utilities.h"


int main(){
    // For the evaluation to take place at compile time, we have
    // to remember to store the return value in a constexpr result variable.
    int run_time_mulitplier {10}; // Run time

    get_value(10); // Compile time

    /*
    int result = get_value(run_time_mulitplier); // run_time_multiplier is not a compile time value. Error
    fmt::println("value: {}", result);
    */
    
}