#ifndef IDENTIFIER_LIST_H_
#define IDENTIFIER_LIST_H_

#include "Lex.h"

class IdentifierList
{
  public:
    
    IdentifierList();
    ~IdentifierList();

    void setID(Token* inputID);

    void addID(Token* inputID);

    int getListSize();

    std::string toString();

  private:

    Token* Id;
    vector<Token*> IDTail;
    int listSize;

};

#endif
