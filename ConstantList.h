#ifndef CONSTANTLIST_H_
#define CONSTANTLIST_H_

#include "Lex.h"
#include <iostream>

class ConstantList
{

  public:

    ConstantList();
    ~ConstantList();

    void setString(Token* inputString);

    void addString(Token* inputString);

    int getSize();

    std::string toString();

    vector<Token*>* getConstants();

  private:

    Token* BigDaddyString;
    
    vector<Token*> StringList;

    int listSize;

};

#endif
