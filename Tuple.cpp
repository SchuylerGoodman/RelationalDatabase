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

bool operator<(Tuple& t1, Tuple& t2)
{
    for(int i = 0; i < t1.getPairs()->size(); i++)
    {
        cout << "in tuple operator" << endl;
        if((*(t1.getPairs()))[i] < (*(t2.getPairs()))[i])
        {
            return true;
        }
        else if((*(t2.getPairs()))[i] < (*(t1.getPairs()))[i])
        {
            return false;
        }
    }
    return false;
}

bool operator==(Tuple& t1, Tuple& t2)
{
    for(int i = 0; i < t1.getPairs()->size(); i++)
    {
        cout << "in tuple == operator" << endl;
        if((*(t1.getPairs()))[i]->second->getTokensValue() == (*(t2.getPairs()))[i]->second->getTokensValue())
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
