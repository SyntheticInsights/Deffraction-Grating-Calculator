#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {

	//Constants
	const double PI = 3.141592653589793;

	//Inputs
	double waveLength_nm, gratingLinesper_mm;

	cout << "Enter wavelength (nm): ";
	cin >> waveLength_nm;

	cout << "Enter grating lines per mm: ";
	cin >> gratingLinesper_mm;

	if (waveLength_nm <= 0 || gratingLinesper_mm <= 0 ) {
		cout << "Invalid input values. All inputs must be positive. \n";
		return 1;
	}

	//Unit Conversion
	double waveLength_m = waveLength_nm * 1e-9;
	double d = 1.0 / (gratingLinesper_mm * 1000); //Spacing in meters

	//Angle Calculation (Multiple Order Considerations)
	int maxOrder = static_cast<int>(d / waveLength_m);
	cout << "\nMaximum possible diffraction order: " << maxOrder << "\n";

	for (int n = 1; n <= maxOrder; ++n) {
		double argument = (n * waveLength_m) / d;

		if (argument > 1.0) {
			if (argument < 1.000001) argument = 1.0;
			else {
				cout << "Order " << n << ": No solution (angle exceeds physical limit).\n";
				continue;
			}
		}

		double theta_rad = asin(argument);
		double theta_deg = theta_rad * (180.0 / PI);
		cout << fixed << setprecision(4);
		cout << "Order: " << n << ", " << theta_deg << " degrees (" << theta_rad << " radians) \n";
	}

	return 0;
}
