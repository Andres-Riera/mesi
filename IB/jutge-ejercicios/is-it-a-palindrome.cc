#include <string>

bool is_palindrome(const std::string& s) {
  int j = s.size() - 1;
  for (int i = 0; i < s.size(); i++) {
    if (s[j] != s[i]) {
      return false;
    }
    j--;
  }
  return true;
}
