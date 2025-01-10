#include <iostream>

bool is_valid_date(int day, int month, int year) {
    if (day > 31 || day < 1 || month < 1 || month > 12 || year < 1800) {
      return false;
    }
    else if (month <= 7 && month != 2) {
      if (month % 2 == 0 && day <= 30) {
        return true;
      } else if (month % 2 != 0) {
        if (day > 31) {
          return false;
        } else {
          return true;
        }
      } else {
        return false;
      }
    } else if (month > 7) {
      if (month % 2 == 0 && day <= 31) {
        return true;
      } else if (month % 2 != 0) {
        if (day > 30) {
          return false;
        } else {
          return true;
        }
      }
    } else if (month == 2 && year % 4 == 0 && day <= 29) {
      if (year % 400 == 0) {
        return true;
      } else if (year % 100 == 0 && day == 29) {
        return false;
      } else {
        return true;
      }
    } else {
      if (day > 28) {
        return false;
      } else {
        return true;
      }
    }
}
