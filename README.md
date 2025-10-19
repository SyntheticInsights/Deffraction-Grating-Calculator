Diffraction Angle Calculator

C++ program to calculate the diffraction angle for a given wavelength, diffraction grating, and order using the grating equation.

Computes diffraction angle in degrees (and radians).

Validates input and handles cases where no physical solution exists.

Supports any wavelength (nm), grating lines density (lines/mm), and diffraction order.

The diffraction grating equation is given by:

$$
d \cdot \sin(\theta) = n \cdot \lambda
$$

Where:  
- \(d\) = spacing between adjacent slits in the grating  
- \(\theta\) = angle of the diffracted maximum  
- \(n\) = order of the maximum (integer: 0, 1, 2, …)  
- \(\lambda\) = wavelength of the light

It converts user input to SI units and calculates the angle using asin. If the calculated sine exceeds 1, the program informs the user that no solution exists.

Requirements

C++ compiler supporting C++11 or higher.

Standard libraries: <iostream>, <cmath>, <iomanip>
