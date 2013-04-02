#include "Schema.h"

Schema::Schema()
{
    schematics = 0;
}

Schema::Schema(IdentifierList* inputIdList)
{
    setSchematics(inputIdList);
}

Schema::Schema(const Schema& inputSchema)
{
    schematics = new vector<Token>(*inputSchema.getSchematics());
}

Schema::Schema(vector<Token>& inputTokens)
{
    schematics = new vector<Token>();
    for(int i = 0; i < inputTokens.size(); i++)
    {
        Token newToken(inputTokens[i]);
        schematics->push_back(newToken);
    }
}

Schema::~Schema()
{
}

vector<Token>* Schema::getSchematics() const
{
    return schematics;
}

void Schema::renameTokenAt(int index, Token& inputToken)
{
    (*schematics)[index] = inputToken;
    return;
}

void Schema::removeTokenAt(int index)
{
    for(int i = index; i < schematics->size() - 1; i++)
    {
        (*schematics)[i] = (*schematics)[i + 1];
    }
    schematics->pop_back();
}

int Schema::getListSize()
{
    return schematics->size();
}

string Schema::toString()
{
    string out;
    for(int i = 0; i < schematics->size(); i++)
    {
        out += "  " + (*schematics)[i].getTokensValue() + " ";
    }
    return out;
}

vector<Token> Schema::getTVecFromSchema()
{
    vector<Token> newVec;
    for(int i = 0; i < schematics->size(); i++)
    {
        Token newToken((*schematics)[i]);
        newVec.push_back(newToken);
    }
    return newVec;
}

Token Schema::operator[](int index)
{
    return (*schematics)[index];
}

void Schema::setSchematics(IdentifierList* inputIdList)
{
    schematics = new vector<Token>();
    vector<Token*> IDTokens = (*inputIdList->getIDs());
    for(int i = 0; i < IDTokens.size(); i++)
    {
        Token newToken = (*IDTokens[i]);
        schematics->push_back(newToken);
    }
    return;
}
