#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {

	//Constants
	const double PI = 3.141592653589793;

	//Inputs
	double waveLength_nm, gratingLinesper_mm;
	int order;

	cout << "Enter wavelength (nm): ";
	cin >> waveLength_nm;

	cout << "Enter grating lines per mm: ";
	cin >> gratingLinesper_mm;

	cout << "Enter diffraction order (n): ";
	cin >> order;

	if (waveLength_nm <= 0 || gratingLinesper_mm <= 0 || order <= 0) {
		cout << "Invalid input values. All inputs must be positive. \n";
		return 1;
	}

	//Unit Conversion
	double waveLength_m = waveLength_nm * 1e-9;
	double d = 1.0 / (gratingLinesper_mm * 1000); //Spacing in meters

	//Angle Calculation
	double argument = (order * waveLength_m) / d;
	if (argument > 1.0) {
		if (argument < 1.000001) argument = 1.0; //Corrects for floating point precision issues.
		cout << "No solution: Angle exceeds physical limits.\n";
	}
	else {
		double theta_rad = asin(argument);
		double theta_deg = theta_rad * (180.0 / PI);
		cout << fixed << setprecision(4);
		cout << "Diffraction Angle: " << theta_deg << " Degrees (" << theta_rad << "Radians)\n";
	}

	return 0;
}
