#include "Schema.h"

Schema::Schema()
{
    schematics = 0;
}

Schema::Schema(IdentifierList* inputIdList)
{
    setSchematics(inputIdList);
}

Schema::~Schema()
{
}

vector<Token*>* Schema::getSchematics()
{
    return schematics;
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
