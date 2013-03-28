#include "Tuple.h"

Tuple::Tuple()
{
}

Tuple::~Tuple()
{
}

Tuple::Tuple(const Tuple& inputTuple)
{
    pairs = inputTuple.getPairs();
}

Tuple::Tuple(Schema* inputSchema, ConstantList* inputConstantList)
{
    vector<Token*>* constants = inputConstantList->getConstants();
    for(int i = 0; i < constants->size(); i++)
    {
        tuplePair p((*(*inputSchema->getSchematics())[i]), (*(*constants)[i]));
        pairs.push_back(p);
    }
}

void Tuple::setPairs(vector<tuplePair> inputPairs)
{
    pairs = inputPairs;
    return;
}

tuplePair Tuple::getTuplePairAt(int index) const
{
    return pairs[index];
}

void Tuple::removePairWithout(set< pair<Token, Token> >* inputTokens)
{
    int oldPairSize = 0;
    while(oldPairSize != pairs.size())
    {
        int i = 0;
        oldPairSize = pairs.size();
        while(i < pairs.size())
        {
            bool remove = true;
            for(set< pair<Token, Token> >::iterator it = inputTokens->begin(); it != inputTokens->end(); it++)
            {
                pair<Token, Token> thisPair = (*it);
                if(thisPair.first.getTokensValue() == pairs[i].first.getTokensValue())
                {
                    remove = false;
                }
            }
            if(remove)
            {
                this->removePairAt(i);
            }
            i += 1;
        }
    }
}

vector<tuplePair> Tuple::getPairs() const
{
    return pairs;
}

Token Tuple::getTokenFromPairAt(int index)
{
    return pairs[index].second;
}

void Tuple::renameTokenSchemaAt(int index, Token& inputToken)
{
    pairs[index].first.setTokenValue(inputToken.getTokensValue());
    return;
}

void Tuple::removePairAt(int index)
{
    for(int i = index; i < pairs.size() - 1; i++)
    {
        pairs[i] = pairs[i + 1];
    }
    pairs.pop_back();
}

int Tuple::getPairVectorSize() const
{
    return pairs.size();
}

string Tuple::toString()
{
    string out = "";
    vector<Token> inTokens;
    for(int i = 0; i < pairs.size(); i++)
    {
        bool add = true;
        for(int j = 0; j < inTokens.size(); j++)
        {
            if(pairs[i].first.getTokensValue() == inTokens[j].getTokensValue())
            {
                add = false;
            }
        }
        if(add)
        {
            inTokens.push_back(pairs[i].first);
            out += pairs[i].first.getTokensValue();
            out += "=" + pairs[i].second.getTokensValue();
            if(i != pairs.size() - 1)
            {
                out += ", ";
            }
        }
    }
    return out;
}

bool operator<(const Tuple& t1, const Tuple& t2)
{
    Tuple nct1 = t1;
    Tuple nct2 = t2;
    for(int i = 0; i < nct1.getPairs().size(); i++)
    {
        if(nct1.getPairs()[i] < nct2.getPairs()[i])
        {
            return true;
        }
        else if(nct2.getPairs()[i] < nct1.getPairs()[i])
        {
            return false;
        }
    }
    return false;
}
