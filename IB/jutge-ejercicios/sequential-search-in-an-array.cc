#include <vector>

bool exists(int x, const std::vector<int>& v) {
  for (int i = 0; i < v.size(); i++) {
    if (x == v[i]) {
      return true;
    }
  }
  return false;
}
