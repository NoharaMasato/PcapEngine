#ifndef IPV4_H_
#define IPV4_H_

#include <array>
#include <iostream>
#include <sstream>
#include <string>

class ipv4 {
  std::array<unsigned char, 4> data;

 public:
  // constructor
  constexpr ipv4() : ipv4(0, 0, 0, 0){};
  constexpr ipv4(unsigned char const a, unsigned char const b,
                 unsigned char const c, unsigned char const d)
      : data{{a, b, c, d}} {};
  explicit constexpr ipv4(unsigned long a)
      : ipv4(static_cast<unsigned char>((a >> 24) & 0xFF),
             static_cast<unsigned char>((a >> 16) & 0xFF),
             static_cast<unsigned char>((a >> 8) & 0xFF),
             static_cast<unsigned char>(a & 0xFF)){};

  // copy constructor
  ipv4(ipv4 const& other) noexcept;

  // cast
  std::string to_string() const;
  constexpr unsigned long to_ulong() const noexcept {
    return (static_cast<unsigned long>(data[0]) << 24) |
           (static_cast<unsigned long>(data[1]) << 16) |
           (static_cast<unsigned long>(data[2]) << 8) |
           static_cast<unsigned long>(data[3]);
  }

  // operator
  ipv4& operator=(ipv4 const& other) noexcept;
  friend std::ostream& operator<<(std::ostream& os, const ipv4& a);
  friend std::istream& operator>>(std::istream& is, ipv4& a);
};

#endif