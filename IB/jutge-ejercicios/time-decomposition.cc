#include <iostream>

void Time(int& hours, int& minutes, int& seconds) {
  while (seconds >= 60) {
    minutes = minutes + 1;
    seconds = seconds - 60;
  }
  while (minutes >= 60) {
    hours = hours + 1;
    minutes = minutes - 60;
  }
}

int main() {
  int seconds;
  std::cin >> seconds;
  int minutes {0};
  int hours {0};
  Time (hours, minutes, seconds);
  std::cout << hours << " " << minutes << " " << seconds << std::endl;

  return 0;
}
