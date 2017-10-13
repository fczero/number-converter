#ifndef INTEGERNUMBER_H
#define INTEGERNUMBER_H
#include "Number.hpp"

class Integer : public Number {
public:
  virtual bool parse();
  Integer(int inputNum=0);
  const Integer operator+(const Integer &other) const;
  const Integer operator-(const Integer &other) const;
  const Integer operator*(const Integer &other) const;
  const Integer operator/(const Integer &other) const;
  const Integer operator%(const Integer &other) const;
  bool operator<(const Integer &rhs) const;
  bool operator>(const Integer &rhs) const;
  bool operator<=(const Integer &rhs) const;
  bool operator>=(const Integer &rhs) const;
  bool operator!=(const Integer &rhs) const;
  bool operator==(const Integer &rhs) const;
protected:
private:
};
#endif // INTEGERNUMBER_H
