
#include "Number.hpp"

const std::string Number::WordNumOnes_[ONES_TABLE_MAX]={"zero","one","two","three","four",
                      "five", "six","seven","eight","nine","ten",
                      "eleven","twelve","thirteen","fourteen","fifteen",
                      "sixteen","seventeen","eighteen","nineteen"
                   };

const std::string Number::WordNumTens_[TENS_TABLE_MAX]={"zero","ten","twenty","thirty","forty",
                      "fifty","sixty","seventy","eighty","ninety"
                   };
const std::string Number:: WordPlaces_[MAX_PLACES]={"","","hundred","thousand"};

Number::Number(){
  numericalValue_ = 0;
}

Number::~Number(){

}

int Number::toInteger(){
    return numericalValue_;
}

std::string Number::toRomanNumeral(){
  std::string returnValue = "";
  int number = numericalValue_;

  if(number >= 0){
      do{
        returnValue += getNumeral(number);
      }while(number>0);
  }
  else{
    returnValue = "INVALID";
  }

  return returnValue;
}

std::string Number::getNumeral(int &number){
    if (number == M){
            number=0;
    return "M";
    }else if (number >= C){
        return getNumeralSequence("CDM",number,M);
    }else if (number >= X){
        return getNumeralSequence("XLC",number,C);
    }else{
        return getNumeralSequence("IVX",number,X);
    }
}

std::string Number::getNumeralSequence(std::string pattern, int &number, Numerals highest){
    std::string result;
    int temp =0;

    if (number/(highest/X) == I){
        subtractFromNumber(number,(highest/X));
        result = getSingleNumeral(pattern,0);
    }else if ((number/(highest/X)) == V){
        subtractFromNumber(number,(highest/X*V));
        result = getSingleNumeral(pattern,1);
    }else if ((number/(highest/X)) == (V-I)){
        subtractFromNumber(number,(highest/X)*(V-I));
        result = getTwoNumeral(pattern,0,1);
    }else if ((number/(highest/X)) == (X-I)){
        subtractFromNumber(number,(highest/X)*(X-I));
        result = getTwoNumeral(pattern,0,2);
    }else if ((number/(highest/X)) > V){
        temp=(number/(highest/X))-V;
        subtractFromNumber(number,(number/(highest/X))*(highest/X));
        result = getMultipleNumeral(pattern,temp).insert(0,pattern,1,1);
    }else if ((number/(highest/X)) < V){
        temp=(number/(highest/X));
        subtractFromNumber(number,(temp*(highest/X)));
        result = getMultipleNumeral(pattern,temp);
    }

    return result;
}

void Number::subtractFromNumber(int &number, int value){
    number-=value;
}

std::string Number::getSingleNumeral(std::string pattern,int index){
    std::string sequence ="";
    return sequence+=pattern[index];
}

std::string Number::getTwoNumeral(std::string pattern,int indexOne, int indexTwo){
    std::string sequence ="";
    sequence+=pattern[indexOne];
    return sequence+=pattern[indexTwo];
}

std::string Number::getMultipleNumeral(std::string pattern, int size){
    std::string sequence ="";
    for(int i=0;i<size;i++)
    sequence+=pattern[0];
    return sequence;
}

std::string Number::toWordNumber(){
  std::string returnValue = "";
  int workingValue = numericalValue_;

  if (numericalValue_ == INVALID_VALUE)
    return "INVALID";
  if (workingValue == 1000)
    returnValue += convertToWord(THOUSANDS_INDEX,workingValue, WordNumOnes_);
  if (workingValue >= 100)
    returnValue += convertToWord(HUNDREDS_INDEX,workingValue, WordNumOnes_);
  if (workingValue >= 20)
    returnValue += convertToWord(TENS_INDEX,workingValue, WordNumTens_);
  if ((workingValue > 0) && (workingValue < 20))
    returnValue += convertToWord(ONES_INDEX,workingValue,WordNumOnes_);
  if ((workingValue == 0) && (returnValue.empty()))
    returnValue += convertToWord(ONES_INDEX,workingValue,WordNumOnes_);

  return returnValue;
}

std::string Number::convertToWord(int dPlace, int& workingValue,
  const std::string WordTable[])
{
  std::string returnValue = "";
  int decimalPlace = computeDecimal(dPlace);

  returnValue += WordTable[workingValue/decimalPlace];
  if (!WordPlaces_[dPlace].empty())
  {
    returnValue += " ";
    returnValue += WordPlaces_[dPlace];
  }
  workingValue %= decimalPlace;
  if (workingValue!=0)
    returnValue += " ";
  return returnValue;
}

int Number::computeDecimal(int input)
{
  int returnValue = 1;

  for(int ctr=input; ctr>0; ctr--)
    returnValue *= 10;

  return returnValue;
}

bool Number::isNumericalValueValid(void)
{
  if (numericalValue_ < 0)
    return false;
  else if (numericalValue_ > 1000)
    return false;
  else
    return true;
}

bool Number::isValid(int inputNumber)
{
  return (inputNumber != INVALID_VALUE);
}
