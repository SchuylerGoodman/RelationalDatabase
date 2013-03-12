#include "Predicate.h"

Predicate::Predicate()
{
    parameterList = 0;
    Id = 0;
}

Predicate::~Predicate()
{

}

void Predicate::setID(Token* inputID)
{
    Id = inputID;
    return;
}

void Predicate::setParameterList(ParameterList* inputParameterList)
{
    parameterList = inputParameterList;
    return;
}

int Predicate::getSize()
{
    return parameterList->getSize() + 1;
}

std::string Predicate::toString()
{
    std::string out;
    out += Id->getTokensValue();
    out += "(";
    out += parameterList->toString();
    out += ")";
    return out;
}

Token* Predicate::getPredicateID()
{
    return Id;
}

ParameterList* Predicate::getParameterList()
{
    return parameterList;
}
