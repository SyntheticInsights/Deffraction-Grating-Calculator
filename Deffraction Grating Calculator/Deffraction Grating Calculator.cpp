#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

constexpr double PI = 3.141592653589793;

// ANSI escape codes for coloring
constexpr char RED[] = "\033[31m";
constexpr char GREEN[] = "\033[32m";
constexpr char RESET[] = "\033[0m";

void userInput(double& waveLength_nm, double& gratingLinesper_mm);
void convertUnits(double waveLength_nm, double gratingLinesper_mm, double& waveLength_m, double& d);
bool calculateAngle(double waveLength_m, double d, int n, double& theta_rad, double epsilon = 1e-6);
void printAngle(int n, double theta_rad);

int main() {

	char repeatCalculation = 'y';

	while (repeatCalculation == 'y' || repeatCalculation == 'Y') {

		double waveLength_nm, gratingLinesper_mm;
		userInput(waveLength_nm, gratingLinesper_mm);

		double waveLength_m, d;
		convertUnits(waveLength_nm, gratingLinesper_mm, waveLength_m, d);

		int orderChoice;
		do {
			cout << "Option 1: Calculate a single order. Option 2: Calculate all possible orders. Enter option 1 or 2\n";
			cin >> orderChoice;

			if (cin.fail() || (orderChoice != 1 && orderChoice != 2)) {
				cin.clear(); //Clear error flag.
				cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Discard invalid input.
				cout << "Invalid option. Please enter 1 or 2.\n";
				orderChoice = 0;
			}
		} while (orderChoice == 0);

		int maxOrder = static_cast<int> (d / waveLength_m);
		cout << "Maximum possible diffraction order " << maxOrder << "\n";

		if (orderChoice == 1) {
			int n;
			do {
				cout << "Enter diffraction order to calculate: (1 - " << maxOrder << "): ";
				cin >> n;
				if (cin.fail() || n < 1 || n > maxOrder) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Enter diffraction order between 1 and " << maxOrder << ".\n";
					n = 0;
				}
			} while (n == 0);

			double theta_rad;
			if (calculateAngle(waveLength_m, d, n, theta_rad)) {
				printAngle(n, theta_rad);
			}
			else {
				cout << "Order: " << n << " No solution (angle exceeds physical limits).\n";
			}
		}
		else if (orderChoice == 2) {

			cout << GREEN << "Valid orders" << RESET << " | " << RED << "Invalid orders" << RESET << "\n";
			cout << left << setw(10) << "Order" << setw(15) << "Angle (degrees)" << setw(15) << "Angle (radians)" << "\n";
			cout << string(40, '-') << "\n";

			for (int n = 1; n <= maxOrder; ++n) {
				double theta_rad;
				if (calculateAngle(waveLength_m, d, n, theta_rad)) {
					cout << left << setw(10) << n
						<< setw(15) << fixed << setprecision(4) << theta_rad * 180.0 / PI
						<< setw(15) << theta_rad << "\n";
				}
				else {
					cout << left << setw(10) << n << setw(15) << "--" << setw(15) << "--" << "\n";
				}
			}
		}

		cout << "Do you want to perform another calculation? (y/n): ";
		cin >> repeatCalculation;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "\n";
    }

	cout << "Exiting program. Goodbye and Thank you!\n";

	return 0;

}

void userInput(double& waveLength_nm, double& gratingLinesper_mm) {
	do {
		cout << "Enter Wavelength (nm): ";
		cin >> waveLength_nm;
		if (cin.fail() || waveLength_nm <= 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Wavelength must be a positive number.\n";
			waveLength_nm = 0;
		}
	} while (waveLength_nm == 0);

	do {
		cout << "Enter Grating Lines per mm: ";
		cin >> gratingLinesper_mm;
		if (cin.fail() || gratingLinesper_mm <= 0) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Grating lines per mm must be a positive number.\n";
			gratingLinesper_mm = 0;
		}
	} while (gratingLinesper_mm == 0);
}

void convertUnits(double waveLength_nm, double gratingLinesper_mm, double &waveLength_m, double &d) {
	waveLength_m = waveLength_nm * 1e-9; //Convert nm to m.
	d = 1.0 / (gratingLinesper_mm * 1000); //Convert lines per mm into line per meters.
	cout << "Wavelength: " << waveLength_m << " m, Grating Spacing: " << d << " m\n";
}

bool calculateAngle(double waveLength_m, double d, int n, double &theta_rad, double epsilon) {
	double argument = (n * waveLength_m) / d;
	if (argument > 1.0) {
		if (argument >= 1.0 - epsilon) argument = 1.0; //Floating point fix.
		else return false; //No solution.
	}
	theta_rad = asin(argument);
	return true;
}

void printAngle(int n, double theta_rad) {
	double theta_deg = theta_rad * 180.0 / PI;
	cout << fixed << setprecision(4);
	cout << "Order: " << n << ", " << theta_deg << " degrees (" << theta_rad << " radians)\n";
}