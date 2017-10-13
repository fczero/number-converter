#include "StringNumber.hpp"

bool StringNumber::parse(){
  fillMapWithWordTable(WordNumMap_,WordNumOnes_,ONES_TABLE_MAX,1);
  fillMapWithWordTable(WordNumMap_,WordNumTens_,TENS_TABLE_MAX,10);
  fillMapWithWordTable(WordPlacesMap_,WordPlaces_,MAX_PLACES,1);

  tokenizeInputString();

  if (!areTokensValid(WordNumMap_))
  {
    if (!areTokensValid(WordPlacesMap_))
      return false;
  }
  else
    numericalValue_ = getDequeTotal();
  return isNumericalValueValid();
}

StringNumber::StringNumber(std::string inputString)
{
  tempInputBuffer_ = inputString;
  if (!parse())
    numericalValue_ = INVALID_VALUE;
}

void StringNumber::fillMapWithWordTable(std::map<std::string, int>& mapInput,
  const std::string WordTable[], int WordTableMax, int multiplier)
{
  for (int ctr=0;ctr<WordTableMax;ctr++)
  mapInput[WordTable[ctr]]= ctr * multiplier;
}

void StringNumber::tokenizeInputString(void)
{
  std::string s = tempInputBuffer_;
  std::string delim = " ";
  std::string token;
  size_t start = 0;
  size_t end = s.find(delim);

  inputTokens_.clear();
  while (end != std::string::npos)
  {
    //#DEBUG
    // std::cout << s.substr(start, end - start) << std::endl;
    inputTokens_.push_back(s.substr(start, end - start));
    start = end + delim.length();
    end = s.find(delim, start);
  }
  //#DEBUG
  // std::cout << s.substr(start, end - start) << std::endl;
  inputTokens_.push_back(s.substr(start, end));
}

bool StringNumber::areTokensValid(const std::map<std::string, int>& WordTable)
{
  std::map<std::string, int>::iterator it;

  for (unsigned int ctr=0;ctr < inputTokens_.size();ctr++)
  {
    if (!(isNumber(inputTokens_[ctr])) && (!(isPlaces(inputTokens_[ctr]))))
      return false;
  }

  return true;
}

int StringNumber::getDequeTotal(void)
{
  int oldDecimalPlace = 0;
  int newDecimalPlace = 0;
  int runningTotal = 0;
  std::string currentToken;
  int tokenValue = 0;

  if (!(isNumber(inputTokens_[0])))
    return INVALID_VALUE;

  if (inputTokens_.size() == 1)
    return tokenToNumber(inputTokens_[0]);

  while(!inputTokens_.empty())
  {
    currentToken = inputTokens_.back();
    if(isPlaces(currentToken))
    {
      tokenValue = getNumberWithPlaces();
      if(!isValid(tokenValue))
        return INVALID_VALUE;
    }
    else if (isNumber(currentToken))
      tokenValue = tokenToNumber(currentToken);

    oldDecimalPlace = getDecimalPlace(runningTotal);
    newDecimalPlace = getDecimalPlace(tokenValue);
//    //#DEBUG
//     std::cout << "runningTotal: "<<runningTotal << std::endl;
//     std::cout << "tokenValue: "<<tokenValue << std::endl;
//     std::cout << "oldDecimalPlace: "<<oldDecimalPlace << std::endl;
//     std::cout << "newDecimalPlace: "<<newDecimalPlace <<"---"<< std::endl;
    if ((!runningTotal)&&(tokenValue))
      runningTotal += tokenValue;
    else if((newDecimalPlace > oldDecimalPlace) && (!isSingleWordNumber(tokenValue)))
      runningTotal += tokenValue;
    else
      return INVALID_VALUE;

    inputTokens_.pop_back();
  }

  return runningTotal;
}

int StringNumber::tokenToMultiplier(std::string inputString)
{
  std::map<std::string, int>::iterator it;

  it = WordPlacesMap_.find(inputString);
  if (it == WordPlacesMap_.end())
    return INVALID_VALUE;
  else
    return (computeDecimal(it->second));
}

int StringNumber::tokenToNumber(std::string inputString)
{
  std::map<std::string, int>::iterator it;

  it = WordNumMap_.find(inputString);
  if (it == WordNumMap_.end())
    return INVALID_VALUE;
  else
    return (it->second);
}

int StringNumber::getNumberWithPlaces(void)
{
  int returnValue = 0;
  int numberToken = 0;

  returnValue = tokenToMultiplier(inputTokens_.back());
  inputTokens_.pop_back();
  numberToken = tokenToNumber(inputTokens_.back());
  if ((isOnes(numberToken)) && (numberToken > 0))
    return (returnValue *= numberToken);
  else
    return INVALID_VALUE;
}

bool StringNumber::isNumber(std::string inputString)
{
  std::map<std::string, int>::iterator it;

  it = WordNumMap_.find(inputString);
  return (!(it == WordNumMap_.end()));
}

bool StringNumber::isPlaces(std::string inputString)
{
  std::map<std::string, int>::iterator it;

  it = WordPlacesMap_.find(inputString);
  return (!(it == WordPlacesMap_.end()));
}

bool StringNumber::isSingleWordNumber(int inputNumber)
{
  return ((0 <= inputNumber)&&(inputNumber < 20));
}

bool StringNumber::isOnes(int tokenValue)
{
  return ((0 <= tokenValue) && (tokenValue < 10));
}

bool StringNumber::isTens(int tokenValue)
{
  return ((10 <= tokenValue) && (tokenValue < 100));
}

bool StringNumber::isHundreds(int tokenValue)
{
  return ((100 <= tokenValue) && (tokenValue < 1000));
}

bool StringNumber::isThousand(int tokenValue)
{
  return (tokenValue == 1000);
}

int StringNumber::getDecimalPlace(int tokenValue)
{
  if (isThousand(tokenValue))
    return THOUSANDS_INDEX;
  else if (isHundreds(tokenValue))
    return HUNDREDS_INDEX;
  else if (isTens(tokenValue))
    return TENS_INDEX;
  else if (isOnes(tokenValue))
    return ONES_INDEX;
  else
    return INVALID_VALUE;
}
const StringNumber StringNumber::operator+(const StringNumber &other) const{
  StringNumber sum = *this;
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

const StringNumber StringNumber::operator-(const StringNumber &other) const{
  StringNumber difference = *this;
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
const StringNumber StringNumber::operator*(const StringNumber &other) const{
  StringNumber product = *this;
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
const StringNumber StringNumber::operator/(const StringNumber &other) const{
  StringNumber quotient = *this;
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
const StringNumber StringNumber::operator%(const StringNumber &other) const{
  StringNumber modulo = *this;
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
bool StringNumber::operator<(const StringNumber &rhs) const{
  if (this->numericalValue_==INVALID_VALUE || rhs.numericalValue_==INVALID_VALUE)
      return false;
  if(this->numericalValue_ < rhs.numericalValue_)
      return true;
  return false;
}
bool StringNumber::operator>(const StringNumber &rhs) const{
  if (this->numericalValue_==INVALID_VALUE || rhs.numericalValue_==INVALID_VALUE)
      return false;
  if(this->numericalValue_ > rhs.numericalValue_)
      return true;
  return false;
}
bool StringNumber::operator<=(const StringNumber &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ <= rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return true;
  return false;
}
bool StringNumber::operator>=(const StringNumber &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ >= rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return true;
  return false;
}
bool StringNumber::operator==(const StringNumber &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ == rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return true;
  return false;
}
bool StringNumber::operator!=(const StringNumber &rhs) const{
  if (this->numericalValue_!=INVALID_VALUE && rhs.numericalValue_!=INVALID_VALUE)
      return this->numericalValue_ != rhs.numericalValue_;
  if(this->numericalValue_==INVALID_VALUE && rhs.numericalValue_==INVALID_VALUE)
      return false;
  return true;
}
