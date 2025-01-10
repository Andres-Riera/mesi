void sort3(int& a, int& b, int& c) {
  if (a >= b) {
    int temp = a;
    a = b;
    b = temp;
  }
  if (b >= c ) {
    int temp = c;
    c = b;
    b = temp;
  }
  if (a >= b) {
    int temp = a;
    a = b;
    b = temp;
  }
}
