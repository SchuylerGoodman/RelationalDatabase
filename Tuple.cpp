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

Tuple::Tuple(Tuple& inputTuple, Schema& inputSchema)
{
    vector<tuplePair> inputPairs = inputTuple.getPairs();
    vector<Token>* schemaTokens = inputSchema.getSchematics();
    for(int i = 0; i < inputPairs.size(); i++)
    {
        inputPairs[i].first.setTokenValue((*schemaTokens)[i].getTokensValue());
    }
    pairs = inputPairs;
}

Tuple::Tuple(Schema* inputSchema, ConstantList* inputConstantList)
{
    vector<Token*>* constants = inputConstantList->getConstants();
    for(int i = 0; i < constants->size(); i++)
    {
        tuplePair p((*inputSchema->getSchematics())[i], (*(*constants)[i]));
        pairs.push_back(p);
    }
}

Tuple Tuple::removeDuplicates()
{
    Tuple newTuple;
    vector<tuplePair> newPairs;
    vector<pair<Token, vector<int> > > myMap;
    for(int i = 0; i < pairs.size(); i++)
    {
        bool insert = true;
        vector<int> newVec;
        for(int j = 0; j < myMap.size(); j++)
        {
            if(pairs[i].first.getTokensValue() == myMap[j].first.getTokensValue())
            {
                myMap[j].second.push_back(i);
                insert = false;
            }
        }
        if(insert)
        {
            newVec.push_back(i);
            myMap.push_back(pair<Token, vector<int> >(pairs[i].first, newVec));
        }
    }
    for(int i = 0; i < myMap.size(); i++)
    {
        int firstInVector = 0;
        // Add new tuplePair with current map token as first and pair value from first on the current map token's int vector as second
        newPairs.push_back(tuplePair(myMap[i].first, pairs[myMap[i].second[firstInVector] ].second));
    }
    newTuple.setPairs(newPairs);
    return newTuple;
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

void Tuple::removePairWithout(vector<Token>& inputTokens)
{
    int oldPairSize = 0;
    while(oldPairSize != pairs.size())
    {
        int i = 0;
        oldPairSize = pairs.size();
        while(i < pairs.size())
        {
            bool remove = true;
            for(int j = 0; j < inputTokens.size(); j++)
            {
                if(inputTokens[j].getTokensValue() == pairs[i].first.getTokensValue())
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

Tuple Tuple::combineTuples(Tuple& secondTuple)
{
    Tuple newTuple;
    vector<tuplePair> newPairs;
    for(int i = 0; i < pairs.size(); i++)
    {
        newPairs.push_back(tuplePair(pairs[i]));
    }
    for(int i = 0; i < secondTuple.getPairVectorSize(); i++)
    {
        newPairs.push_back(tuplePair(secondTuple.getTuplePairAt(i)));
    }
    newTuple.setPairs(newPairs);
    return newTuple;
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

Token Tuple::operator[](const int& inputInt) const
{
    return pairs[inputInt].first;
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
