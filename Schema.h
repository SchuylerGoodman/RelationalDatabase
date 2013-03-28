#ifndef SCHEMA_H_
#define SCHEMA_H_

#include "Parser.h"

class Schema
{

  public:

    Schema();
    Schema(IdentifierList* inputIdList);
    Schema(Schema& inputSchema);
    ~Schema();

    vector<Token*>* getSchematics();

    void renameTokenAt(int index, Token& inputToken);

    void removeTokenAt(int index);

    int getListSize();

    string toString();

  private:

    void setSchematics(IdentifierList* inputIdList);

    vector<Token*>* schematics;

};

#endif
