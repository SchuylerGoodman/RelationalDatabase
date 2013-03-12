#include "Fact.h"

Fact::Fact()
{
    Id = 0;
    clist = 0;
}

Fact::~Fact()
{

}

void Fact::setID(Token* inputID)
{
    Id = inputID;
    return;
}

void Fact::setConstantList(ConstantList* constantlist)
{
    clist = constantlist;
    return;
}

int Fact::getListSize()
{
    int listSize = clist->getSize() + 1;
    return listSize;
}

std::string Fact::toString()
{
    std::string out;
    out += "\n  " + Id->getTokensValue();
    out += "(" + clist->toString() + ").";
    return out;
}

Token* Fact::getFactID()
{
    return Id;
}

ConstantList* Fact::getConstantList()
{
    return clist;
}
