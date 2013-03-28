#include "Schema.h"

Schema::Schema()
{
    schematics = 0;
}

Schema::Schema(IdentifierList* inputIdList)
{
    setSchematics(inputIdList);
}

Schema::Schema(Schema& inputSchema)
{
    schematics = new vector<Token*>(*inputSchema.getSchematics());
}

Schema::~Schema()
{
}

vector<Token*>* Schema::getSchematics()
{
    return schematics;
}

void Schema::renameTokenAt(int index, Token& inputToken)
{
    (*(*schematics)[index]) = inputToken;
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
        out += "  " + (*schematics)[i]->getTokensValue() + " ";
    }
    return out;
}

void Schema::setSchematics(IdentifierList* inputIdList)
{
    schematics = new vector<Token*>();
    (*schematics) = (*inputIdList->getIDs());
    return;
}
