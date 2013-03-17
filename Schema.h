#ifndef SCHEMA_H_
#define SCHEMA_H_

#include "Parser.h"

class Schema
{

  public:

    Schema();
    Schema(IdentifierList* inputIdList);
    ~Schema();

    vector<Token*>* getSchematics();

    int getListSize();

    string toString();

  private:

    void setSchematics(IdentifierList* inputIdList);

    vector<Token*>* schematics;

};

#endif
