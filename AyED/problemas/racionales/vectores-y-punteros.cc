#include <iostream>
#include <vector>

using namespace std;

void Inversion(vector<int>& vector) {
  vector<int> temp;
  for (int i = vector.size(); i > 0; i--) {
    temp.push_back(vector[i]);
  }
  for (int i = 0; i < temp.size(); i++) {
    vector[i] = temp[i];
  }
}

int main() {
  vector<int> a{1, 2, 3, 5};
  Inversion(a);
  for (n: a) {
    cout << n << " ";
  }
  cout << "\n";
  return 0;
}