#ifndef _MESSAGE_H_
#define _MESSAGE_H_

class Message
{
private:
  Type* type;

public:
  Type* getType(){ return type;}
  void setType(Type* type_) { type = type_; }
};

#endif

