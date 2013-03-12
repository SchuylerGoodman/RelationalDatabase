#include "Scheme.h"

Scheme::Scheme()
{
    Id = 0;
    IDList = 0;
}

Scheme::~Scheme()
{
    delete[] Id;
    delete[] IDList;
}

void Scheme::setID(Token* inputID)
{
    Id = inputID;
    return;
}

void Scheme::setIDList(IdentifierList* identifierlist)
{
    IDList = identifierlist;
    return;
}

int Scheme::getListSize()
{
    int size = IDList->getListSize() + 1;
    return size;
}

std::string Scheme::toString()
{
    string out;
    out += Id->getTokensValue();
    out += "(" + IDList->toString() + ")";
    return out;
}

Token* Scheme::getSchemeID()
{
    return Id;
}

IdentifierList* Scheme::getIDList()
{
    return IDList;
}
