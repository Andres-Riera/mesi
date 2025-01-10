#include <vector>

double scalar_product(const std::vector<double>& u, const std::vector<double>& v) {
  double result {0.0};
  for (int i = 0; i < u.size(); i++) {
    result = result + u[i] * v[i];
  }
  return result;
}

