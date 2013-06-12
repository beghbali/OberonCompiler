#ifndef _VALUE_H_
#define _VALUE_H_

class Value
{
 private:
  union {
    int intval;
    double realval;
    bool boolval;
    char* strval;
    char charval;
  };
 public:
  Value(int intval_) : intval(intval_){  }
  Value(double realval_) : realval(realval_){  }
  Value(bool boolval_) : boolval(boolval_){  }
  Value(char* strval_) : strval(strval_) { }
  Value(char charval_) : charval(charval_) { }

  int getIntValue() { return intval; }
  double getRealValue() { return realval; }
  bool getBoolValue() { return boolval; }
  char* getStringValue() { return strval; }
  char getCharValue() { return charval; }

  void setIntValue(int intval_) { intval = intval_; }
  void setRealValue(double realval_) { realval = realval_; }
  void setBoolValue(bool boolval_) { boolval = boolval_; }
  void setStringValue(char* strval_) { strval = strval_; }
  void setCharValue(char charval_) { charval = charval_; }

  static int parseInt(char* str);  
  static double parseReal(char* str);
  static char parseChar(char* str); 
  static char* boolToString(bool value);
};

#endif
