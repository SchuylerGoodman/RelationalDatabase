#ifndef SCHEME_H_ 
#define SCHEME_H_

#include "IdentifierList.h"

class Scheme
{
  public:
    
    Scheme();
    ~Scheme();

    void setID(Token* inputID);

    void setIDList(IdentifierList* identifierlist);

    int getListSize();

    std::string toString();

    Token* getSchemeID();

    IdentifierList* getIDList();

  private:
    
    Token* Id;
    IdentifierList* IDList;

};

#endif
