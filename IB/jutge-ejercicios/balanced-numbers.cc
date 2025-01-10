bool is_balanced(int n) {
  int copy = n;
  int odds {0};
  int evens {0};
  int digits = n / 10 + 1;
  while (copy > 0) {
    if (digits % 2 == 0) {
      odds += (copy % 100) / 10;
      copy /= 100;
    }
    else {
      odds += copy % 10; 
      copy /= 10;
    }
  }
  copy = n;
  while (copy > 0) {
    if (digits % 2 == 0) {
      if (copy == n) {
        evens += copy % 10;
        copy /= 10;
      }
      else {
        evens += (copy % 100) / 10;
        copy /= 100;
      }
    }
    else {
      evens += copy % 10; 
      copy /= 10;
    } 
  }
  if (odds == evens) {
    return true;
  }
  return false;
}
