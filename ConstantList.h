#ifndef CONSTANTLIST_H_
#define CONSTANTLIST_H_

#include "Lex.h"

class ConstantList
{

  public:

    ConstantList();
    ~ConstantList();

    void setString(Token* inputString);

    void addString(Token* inputString);

    int getSize();

    std::string toString();

  private:

    Token* BigDaddyString;
    
    vector<Token*> StringList;

    int listSize;

};

#endif
