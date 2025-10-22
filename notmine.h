//COPY PASTED FROM SOMEONE ELSES LIBRARY
//I HAVE NO IDEA HOW IT WORKS
// I NEED TO GET BETTER AT MATH
#include "vex.h"

const double PI = 3.14159265358979323846;
// Note: <math.h> and <stdio.h> are assumed to be included via "vex.h" 

/**
 * @brief Converts the angle returned by atan2(y, x) into the [0, 360) degree range.
 * The standard atan2(y, x) returns an angle in radians in the range (-PI, PI], 
 * which corresponds to (-180, 180] degrees. This function converts that value
 * into the positive [0, 360) range.
 *
 * @param y The y-coordinate (or rise). Input is now int.
 * @param x The x-coordinate (or run). Input is now int.
 * @return The angle in degrees, from 0 up to (but not including) 360. Output is now int.
 */
double dir360(int y, int x) {
    // 1. Calculate the angle in radians using the global atan2 function.
    // Inputs are cast to double for floating-point calculation accuracy.
    double radians = atan2((double)y, (double)x);
    
    // 2. Convert the radians to degrees.
    // degrees = radians * (180 / PI)
    double degrees = radians * 180.0 / PI;
    
    // 3. Normalize the angle from (-180, 180] to [0, 360).
    // If the angle is negative, add 360 to shift it into the positive range.
    if (degrees < 0) {
        degrees += 360.0;
    }
    
    // 4. Return the result as an integer, truncating the decimal component.
return static_cast<int>(degrees);
}