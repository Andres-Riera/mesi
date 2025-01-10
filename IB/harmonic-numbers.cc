#include <iostream>
#include <iomanip>

int main() {
	double number;
	std::cin >> number;
	double output {0};
	double i = 1; 
	for (double& copy = output ; i <= number; ++i) {
		 copy= copy + 1 / i;
	}
	std::cout << std::fixed;
	std::cout << std::setprecision(4) << output << std::endl;
}
