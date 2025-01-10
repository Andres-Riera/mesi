#include <iostream>
#include <iomanip>
#include <cmath>

bool IsAValidTriangle(const double side1, const double side2, 
                      const double side3) {
  if (side1 > side2 + side3) {
    return false;
  }
  else if (side2 > side3 + side1) {
    return false;
  }
  else if (side3 > side2 + side1) {
    return false;
  }
  return true;
}

double Area(const double side1, const double side2,const double side3) {
  double perimeter = (side1 + side2 + side3) / 2;
  double area = sqrt(perimeter * (perimeter - side1) * (perimeter - side2) * 
                (perimeter - side3));
  return area;
}

int main() {
  double a, b, c;
  std::cin >> a >> b >> c;
  if (!IsAValidTriangle(a, b, c)) {
    std::cout << "Not a valid triangle" << std::endl;
    return 0;
  }
  std::cout << std::fixed << std::setprecision(2) << Area(a, b, c);
  return 0;
}
