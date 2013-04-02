#ifndef SCHEMA_H_
#define SCHEMA_H_

#include "Parser.h"

class Schema
{

  public:

    Schema();
    Schema(IdentifierList* inputIdList);
    Schema(const Schema& inputSchema);
    Schema(vector<Token>& inputTokens);
    ~Schema();

    vector<Token>* getSchematics() const;

    void renameTokenAt(int index, Token& inputToken);

    void removeTokenAt(int index);

    int getListSize();

    string toString();

    vector<Token> getTVecFromSchema();

    Token operator[](int index);

  private:

    void setSchematics(IdentifierList* inputIdList);

    vector<Token>* schematics;

};

#endif
