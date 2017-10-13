#ifndef ROMANNUMERAL_HPP_
#define ROMANNUMERAL_HPP_

#include "Number.hpp"

class RomanNumeral : public Number {
public:
  virtual bool parse();
  RomanNumeral(std::string inputRomanNum="");
  const RomanNumeral operator+(const RomanNumeral &other) const;
  const RomanNumeral operator-(const RomanNumeral &other) const;
  const RomanNumeral operator*(const RomanNumeral &other) const;
  const RomanNumeral operator/(const RomanNumeral &other) const;
  const RomanNumeral operator%(const RomanNumeral &other) const;
  bool operator<(const RomanNumeral &rhs) const;
  bool operator>(const RomanNumeral &rhs) const;
  bool operator<=(const RomanNumeral &rhs) const;
  bool operator>=(const RomanNumeral &rhs) const;
  bool operator!=(const RomanNumeral &rhs) const;
  bool operator==(const RomanNumeral &rhs) const;

protected:
  int getTotal();

private:
  std::string tempRomanBuffer_;
};

#endif // ROMANNUMERAL_HPP_
