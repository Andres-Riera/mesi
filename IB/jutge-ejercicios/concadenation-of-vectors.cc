#include <vector>

std::vector<int> concatenation(const std::vector<int>& v1, const std::vector<int>& v2) {
  std::vector<int> full;
  for (int i = 0; i < v1.size(); i++) {
    full.push_back(v1[i]);
  }
  for (int i = 0; i < v2.size(); i++) {
    full.push_back(v2[i]);
  }
  return full;
}
