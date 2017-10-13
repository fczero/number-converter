#include "IntegerNumber.hpp"


Integer::Integer(int inputNum){
  numericalValue_ = inputNum;
  if (!(parse()))
    numericalValue_ = INVALID_VALUE;
}

bool Integer::parse(){
  return (isNumericalValueValid());
}

const Integer Integer::operator+(const Integer &other) const{
  Integer sum = *this;
  int lhs = sum.numericalValue_;
  int rhs = other.numericalValue_;

  if((lhs != INVALID_VALUE)&&(rhs != INVALID_VALUE))
  {
    sum.numericalValue_ += other.numericalValue_;
    if (!(sum.parse()))
      sum.numericalValue_ = INVALID_VALUE;
  }
  else
    sum.numericalValue_ = INVALID_VALUE;

  return sum;
}

const Integer Integer::operator-(const Integer &other) const{
  Integer difference = *this;
  int lhs = difference.numericalValue_;
  int rhs = other.numericalValue_;

  if((lhs != INVALID_VALUE)&&(rhs != INVALID_VALUE))
  {
    difference.numericalValue_ -= other.numericalValue_;
    if (!(difference.parse()))
      difference.numericalValue_ = INVALID_VALUE;
  }
  else
    difference.numericalValue_ = INVALID_VALUE;

  return difference;
}
const Integer Integer::operator*(const Integer &other) const{
  Integer product = *this;
  int lhs = product.numericalValue_;
  int rhs = other.numericalValue_;

  if((lhs != INVALID_VALUE)&&(rhs != INVALID_VALUE))
  {
    product.numericalValue_ *= other.numericalValue_;
    if (!(product.parse()))
      product.numericalValue_ = INVALID_VALUE;
  }
  else
    product.numericalValue_ = INVALID_VALUE;

  return product;
}
const Integer Integer::operator/(const Integer &other) const{
  Integer quotient = *this;
  int lhs = quotient.numericalValue_;
  int rhs = other.numericalValue_;

  if((lhs != INVALID_VALUE)&&(rhs != INVALID_VALUE)&&(rhs))
  {
    quotient.numericalValue_ /= other.numericalValue_;
    if (!(quotient.parse()))
      quotient.numericalValue_ = INVALID_VALUE;
  }
  else
    quotient.numericalValue_ = INVALID_VALUE;

  return quotient;
}
const Integer Integer::operator%(const Integer &other) const{
  Integer modulo = *this;
  int lhs = modulo.numericalValue_;
  int rhs = other.numericalValue_;

  if((lhs != INVALID_VALUE)&&(rhs != INVALID_VALUE)&&(rhs))
  {
    modulo.numericalValue_ %= other.numericalValue_;
    if (!(modulo.parse()))
      modulo.numericalValue_ = INVALID_VALUE;
  }
  else
    modulo.numericalValue_ = INVALID_VALUE;

  return modulo;

}
bool Integer::operator<(const Integer &rhs) const{
  if (this->numericalValue_==INVALID_VALUE || rhs.numericalValue_==INVALID_VALUE)
      return false;
  if(this->numericalValue_ < rhs.numericalValue_)
      return true;
  return false;
}
bool Integer::operator>(const Integer &rhs) const{
  if (this->numericalValue_==INVALID_VALUE || rhs.numericalValue_==INVALID_VALUE)
      return false;
  if(this->numericalValue_ > rhs.numericalValue_)
      return true;
  return false;
}
bool Integer::operator<=(const Integer &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ <= rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return true;
  return false;
}
bool Integer::operator>=(const Integer &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ >= rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return true;
  return false;
}
bool Integer::operator==(const Integer &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ == rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return true;
  return false;
}
bool Integer::operator!=(const Integer &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ != rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return false;
  return true;
}
