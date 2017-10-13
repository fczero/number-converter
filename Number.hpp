#ifndef NUMBER_H_
#define NUMBER_H_
#include <iostream>
#include <deque>
#include <map>

#define MAX_PLACES 4
#define INVALID_VALUE (-1)
#define ONES_INDEX 0
#define TENS_INDEX 1
#define HUNDREDS_INDEX 2
#define THOUSANDS_INDEX 3
#define ONES_TABLE_MAX 20
#define TENS_TABLE_MAX 10

class Number {
public:
  int toInteger();
  std::string toRomanNumeral();
  std::string toWordNumber();
  virtual bool parse() = 0;
  virtual ~Number();

protected:
  static const std::string WordNumOnes_[ONES_TABLE_MAX];
  static const std::string WordNumTens_[TENS_TABLE_MAX];
  static const std::string WordPlaces_[MAX_PLACES];
  enum Numerals{I=1, V=5, X=10, L=50, C=100, D=500, M=1000};
  int numericalValue_;
  Number();
  std::string convertToWord(int dPlace, int& workingValue,
  const std::string WordTable[]);
  int computeDecimal(int input);
  bool isValid(int inputNumber);
  bool isNumericalValueValid();
  std::string getNumeral(int &number);
  std::string getNumeralSequence(std::string pattern, int &number, Numerals highest);
  void subtractFromNumber(int &number, int value);
  std::string getSingleNumeral(std::string pattern,int index);
  std::string getTwoNumeral(std::string pattern,int indexOne, int indexTwo);
  std::string getMultipleNumeral(std::string pattern, int size);

private:
};


#endif  // NUMBER_H_
