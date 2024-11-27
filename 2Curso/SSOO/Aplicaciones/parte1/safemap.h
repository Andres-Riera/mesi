#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <expected>
#include <string_view>

#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

class SafeMap {
 public:
  explicit SafeMap(std::string_view sv) noexcept : sv_{sv} {}
  explicit SafeMap() noexcept : sv_{nullptr, 0} {}
  SafeMap(const SafeMap&) = delete;
  SafeMap& operator=(const SafeMap&) = delete;
  SafeMap(SafeMap&& other) noexcept {
    sv_ = other.sv_;
    other.sv_ = std::string_view(nullptr, 0);
  }
  SafeMap& operator=(SafeMap&& other) noexcept {
    if (this != &other && sv_ != other.sv_) {
      // Cerrar el descriptor de archivo actual
      munmap(const_cast<char*>(sv_.data()), sv_.size());
      // Mover el descriptor de archivo de 'other' a este objeto
      sv_ = other.sv_;
      other.sv_ = std::string_view(nullptr, 0);
    }
    return *this;
  }
  friend std::ostream& operator<<(std::ostream& os, const SafeMap& safe_map) {
    os.write(safe_map.sv_.data(), safe_map.sv_.size());
    return os;
  }
  ~SafeMap() noexcept {
    munmap(const_cast<char*>(sv_.data()), sv_.size());
  }
  [[nodiscard]] bool is_valid() const noexcept {
    return sv_.data() != nullptr;
  }
  [[nodiscard]] std::string_view get() const noexcept {
    return sv_;
  }
  int get_size() const noexcept {
    return sv_.size();
  }

 private:
  std::string_view sv_;
};