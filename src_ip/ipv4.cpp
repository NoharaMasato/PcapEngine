#include "ipv4.hpp"

ipv4::ipv4(ipv4 const & other) noexcept : data(other.data) {} //コピーコンストラクタ

ipv4& ipv4::operator=(ipv4 const & other) noexcept
{
  data = other.data;
  return *this;
}

std::string ipv4::to_string() const
{
  std::stringstream sstr;
  sstr << *this;
  return sstr.str();
}

std::ostream& operator<<(std::ostream& os, const ipv4& a)
{
  os << static_cast<int>(a.data[0]) << '.'
      << static_cast<int>(a.data[1]) << '.'
      << static_cast<int>(a.data[2]) << '.'
      << static_cast<int>(a.data[3]);
  return os;
}

std::istream& operator>>(std::istream& is, ipv4& a)
{
  char d1, d2, d3;
  int b1, b2, b3, b4;
  is >> b1 >>d1 >> b2 >> d2 >> b3 >> d3 >> b4;
  if(d1 == '.' && d2 == '.' && d3 == '.')
    a = ipv4(b1, b2, b3, b4);
  else
    is.setstate(std::ios_base::failbit);
  return is;
}