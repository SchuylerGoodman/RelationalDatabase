#include "IdentifierList.h"

IdentifierList::IdentifierList()
{
    Id = 0;
    listSize = 0;
}

IdentifierList::~IdentifierList()
{
    delete[] Id;
    for(int i = 0; i < listSize; ++i)
    {
        delete[] IDTail[i];
    }
}

void IdentifierList::setID(Token* inputID)
{
    Id = inputID;
    return;
}

void IdentifierList::addID(Token* inputID)
{
    IDTail.push_back(inputID);
    ++listSize;
    return;
}

int IdentifierList::getListSize()
{
    return listSize;
}

std::string IdentifierList::toString()
{
    string out;
    out += Id->getTokensValue();
    for(int i = 0; i < listSize; ++i)
    {
        out += "," + IDTail[i]->getTokensValue();
    }
    return out;
}

vector<Token*>* IdentifierList::getIDs()
{
    vector<Token*>* IDs = new vector<Token*>();
    IDs->push_back(Id);
    for(int i = 0; i < listSize; i++)
    {
        IDs->push_back(IDTail[i]);
    }
    return IDs;
}
