#include <iostream>
#include <cmath>
using namespace std;

int main() {

	//Constants
	const double PI = 3.141592653589793;

	//Inputs
	double waveLength_nm;
	double gratingLinesper_mm;
	int order;

	cout << "Enter wavelength (nm): ";
	cin >> waveLength_nm;

	cout << "Enter grating lines per mm: ";
	cin >> gratingLinesper_mm;

	cout << "Enter diffration order (n): ";
	cin >> order;

	//Unit Conversion
	double waveLength_m = waveLength_nm * 1e-9;
	double d = 1.0 / (gratingLinesper_mm * 1000); //Spacing in meters

	//Angle Calculation
	double argument = (order * waveLength_m) / d;
	if (argument > 1.0) {
		cout << "No solution: Angle exceeds physical limits.\n";
	}
	else {
		double theta_rad = asin(argument);
		double theta_deg = theta_rad * (180.0 / PI);
		cout << "Diffraction Angle: " << theta_deg << " Degrees\n";
	}

//

	return 0;
}
