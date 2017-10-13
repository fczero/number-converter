#ifndef STRINGNUMBER_H_
#define STRINGNUMBER_H_
#include "Number.hpp"

class StringNumber : public Number {
public:
  virtual bool parse();
  StringNumber(std::string inputString="zero");
  const StringNumber operator+(const StringNumber &other) const;
  const StringNumber operator-(const StringNumber &other) const;
  const StringNumber operator*(const StringNumber &other) const;
  const StringNumber operator/(const StringNumber &other) const;
  const StringNumber operator%(const StringNumber &other) const;
  bool operator<(const StringNumber &rhs) const;
  bool operator>(const StringNumber &rhs) const;
  bool operator<=(const StringNumber &rhs) const;
  bool operator>=(const StringNumber &rhs) const;
  bool operator!=(const StringNumber &rhs) const;
  bool operator==(const StringNumber &rhs) const;

private:
  std::map<std::string, int> WordNumMap_;
  std::map<std::string, int> WordPlacesMap_;
  std::string tempInputBuffer_;
  std::deque<std::string> inputTokens_;

protected:
  void fillMapWithWordTable(std::map<std::string, int>& mapInput,
    const std::string WordTable[], int WordTableMax, int multiplier);
  void tokenizeInputString(void);
  int getDequeTotal(void);
  int getDecimalPlace(int tokenValue);
  int tokenToMultiplier(std::string inputString);
  int tokenToNumber(std::string inputString);
  int getNumberWithPlaces(void);
  bool areTokensValid(const std::map<std::string, int>& WordTable);
  bool isOnes(int tokenValue);
  bool isTens(int tokenValue);
  bool isHundreds(int tokenValue);
  bool isThousand(int tokenValue);
  bool isNumber(std::string inputString);
  bool isPlaces(std::string inputString);
  bool isSingleWordNumber(int inputNumber);
};

#endif  // STRINGNUMBER_H_
