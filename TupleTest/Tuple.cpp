#include "Tuple.h"

Tuple::Tuple()
{
    pairs = 0;
}

Tuple::~Tuple()
{
}

Tuple::Tuple(Schema* inputSchema, ConstantList* inputConstantList)
{
    pairs = new vector<tuplePair*>();
    vector<Token*>* constants = inputConstantList->getConstants();
    for(int i = 0; i < constants->size(); i++)
    {
        tuplePair* p = new tuplePair((*inputSchema->getSchematics())[i], (*constants)[i]);
        pairs->push_back(p);
    }
}

vector<tuplePair*>* Tuple::getPairs()
{
    return pairs;
}

bool operator<(Tuple& t1, Tuple& t2)
{
    for(int i = 0; i < t1.getPairs()->size(); i++)
    {
        if((*t1.getPairs())[i] < (*t2.getPairs())[i])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

string Tuple::toString()
{
    string out = "";
    for(int i = 0; i < pairs->size(); i++)
    {
        out += (*pairs)[i]->second->getTokensValue();
        for(int j = 0; j < (*pairs)[i]->first->getTokensValue().length(); j++)
        {
            out += " ";
        }
    }
    return out;
}
