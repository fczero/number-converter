#include "RomanNumeral.hpp"

enum Numerals{I=1, V=5, X=10, L=50, C=100, D=500, M=1000};

RomanNumeral::RomanNumeral(std::string inputRomanNum){
  tempRomanBuffer_ = inputRomanNum;
  if(!parse())
    numericalValue_ = -1;
}

bool RomanNumeral::parse(){
int thousands=0;
int hundreds=0;
int tens=0;
int ones=0;

    for(unsigned int i=0 ; i<tempRomanBuffer_.length() ; i++){
        if(tempRomanBuffer_[i]=='I'){
            if(ones%V==3 || ones%V==4)
                return false;
            ones+=I;
        }else if(tempRomanBuffer_[i]=='V'){
            if(ones>I)
                return false;
            else if (ones==I)
                ones=V-I;
            else
                ones+=V;
        }else if(tempRomanBuffer_[i]=='X'){
            if(ones>I)
                return false;
            else if (ones==I)
                ones=X-I;
            else if(tens%L==30 || tens%L==40)
                return false;
            else
                tens+=X;
        }else if(tempRomanBuffer_[i]=='L'){
            if(ones!=0 || tens>X)
                return false;
            else if (tens==X)
                tens=L-X;
            else
                tens+=L;
        }else if(tempRomanBuffer_[i]=='C'){
            if(ones!=0 || tens>X)
                return false;
            else if (tens==X)
                tens=C-X;
            else if(hundreds%D==300 || hundreds%D==400)
                return false;
            else
                hundreds+=C;
        }else if(tempRomanBuffer_[i]=='D'){
            if(ones!=0 || tens!=0 || hundreds>C)
                return false;
            else if (hundreds==C)
                hundreds=D-C;
            else
                hundreds+=D;
        }else if(tempRomanBuffer_[i]=='M'){
            if(ones!=0 || tens!=0 || hundreds>C)
                return false;
            else if (hundreds==C)
                hundreds=M-C;
            else if (tempRomanBuffer_.length()!=1)
                return false;
            else
                thousands+=M;
        }else{
            return false;
        }
        if (ones>=X || tens>=C || hundreds>=M || thousands>M)
            return false;
    }

  numericalValue_ = getTotal();

return true;
}

int RomanNumeral::getTotal(){
int thousands=0;
int hundreds=0;
int tens=0;
int ones=0;
    for(unsigned int i=0 ; i<tempRomanBuffer_.length() ; i++){
        if(tempRomanBuffer_[i]=='I'){
            ones+=I;
        }else if(tempRomanBuffer_[i]=='V'){
            if(ones>0)
                ones=V-ones;
            else
                ones+=V;
        }else if(tempRomanBuffer_[i]=='X'){
            if(ones>0)
                ones=X-ones;
            else
            tens+=X;
        }else if(tempRomanBuffer_[i]=='L'){
            if(tens>0)
            tens=L-tens;
            else
                tens+=L;
        }else if(tempRomanBuffer_[i]=='C'){
            if(tens>0)
                tens=C-tens;
            else
            hundreds+=C;
        }else if(tempRomanBuffer_[i]=='D'){
            if (hundreds>0)
                hundreds=D-hundreds;
            else
                hundreds+=D;
        }else if(tempRomanBuffer_[i]=='M'){
            if(hundreds>0)
                hundreds=M-hundreds;
            else
                thousands = M;
        }
    }
  return thousands+hundreds+tens+ones;
}
const RomanNumeral RomanNumeral::operator+(const RomanNumeral &other) const{
  RomanNumeral sum = *this;
  int lhs = sum.numericalValue_;
  int rhs = other.numericalValue_;

  if((lhs != INVALID_VALUE)&&(rhs != INVALID_VALUE))
  {
    sum.numericalValue_ += other.numericalValue_;
    if (!(sum.isNumericalValueValid()))
      sum.numericalValue_ = INVALID_VALUE;
  }
  else
    sum.numericalValue_ = INVALID_VALUE;

  return sum;
}

const RomanNumeral RomanNumeral::operator-(const RomanNumeral &other) const{
  RomanNumeral difference = *this;
  int lhs = difference.numericalValue_;
  int rhs = other.numericalValue_;

  if((lhs != INVALID_VALUE)&&(rhs != INVALID_VALUE))
  {
    difference.numericalValue_ -= other.numericalValue_;
    if (!(difference.isNumericalValueValid()))
      difference.numericalValue_ = INVALID_VALUE;
  }
  else
    difference.numericalValue_ = INVALID_VALUE;

  return difference;
}
const RomanNumeral RomanNumeral::operator*(const RomanNumeral &other) const{
  RomanNumeral product = *this;
  int lhs = product.numericalValue_;
  int rhs = other.numericalValue_;

  if((lhs != INVALID_VALUE)&&(rhs != INVALID_VALUE))
  {
    product.numericalValue_ *= other.numericalValue_;
    if (!(product.isNumericalValueValid()))
      product.numericalValue_ = INVALID_VALUE;
  }
  else
    product.numericalValue_ = INVALID_VALUE;

  return product;
}
const RomanNumeral RomanNumeral::operator/(const RomanNumeral &other) const{
  RomanNumeral quotient = *this;
  int lhs = quotient.numericalValue_;
  int rhs = other.numericalValue_;

  if((lhs != INVALID_VALUE)&&(rhs != INVALID_VALUE)&&(rhs))
  {
    quotient.numericalValue_ /= other.numericalValue_;
    if (!(quotient.isNumericalValueValid()))
      quotient.numericalValue_ = INVALID_VALUE;
  }
  else
    quotient.numericalValue_ = INVALID_VALUE;

  return quotient;
}
const RomanNumeral RomanNumeral::operator%(const RomanNumeral &other) const{
  RomanNumeral modulo = *this;
  int lhs = modulo.numericalValue_;
  int rhs = other.numericalValue_;

  if((lhs != INVALID_VALUE)&&(rhs != INVALID_VALUE)&&(rhs))
  {
    modulo.numericalValue_ %= other.numericalValue_;
    if (!(modulo.isNumericalValueValid()))
      modulo.numericalValue_ = INVALID_VALUE;
  }
  else
    modulo.numericalValue_ = INVALID_VALUE;

  return modulo;

}
bool RomanNumeral::operator<(const RomanNumeral &rhs) const{
  if (this->numericalValue_==INVALID_VALUE || rhs.numericalValue_==INVALID_VALUE)
      return false;
  if(this->numericalValue_ < rhs.numericalValue_)
      return true;
  return false;
}
bool RomanNumeral::operator>(const RomanNumeral &rhs) const{
  if (this->numericalValue_==INVALID_VALUE || rhs.numericalValue_==INVALID_VALUE)
      return false;
  if(this->numericalValue_ > rhs.numericalValue_)
      return true;
  return false;
}
bool RomanNumeral::operator<=(const RomanNumeral &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ <= rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return true;
  return false;
}
bool RomanNumeral::operator>=(const RomanNumeral &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ >= rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return true;
  return false;
}
bool RomanNumeral::operator==(const RomanNumeral &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ == rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return true;
  return false;
}
bool RomanNumeral::operator!=(const RomanNumeral &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ != rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return false;
  return true;
}
