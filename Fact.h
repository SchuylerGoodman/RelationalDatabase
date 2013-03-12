#ifndef FACT_H_
#define FACT_H_

#include "ConstantList.h"

class Fact
{

  public:
    
    Fact();
    ~Fact();

    void setID(Token* inputID);

    void setConstantList(ConstantList* constantlist);

    int getListSize();

    std::string toString();

    Token* getFactID();

    ConstantList* getConstantList();

  private:

    Token* Id;

    ConstantList* clist;

};


#endif
