int number_of_digits(int n) {
  int count {1};
  while (n > 9) {
      count++;
      n /= 10;
  }
  return count;
}
