#pragma once 

// Marking a function as constexpr gives it the potential
// to be evaluated at compile time
/*
constexpr int get_value(int multiplier) {
	return 3 * multiplier; 
}
*/


// Evaluate this function at compile time. If you can't
// do that throw a compiler error
consteval int get_value(int multiplier) {
	 return 3 * multiplier; 
}