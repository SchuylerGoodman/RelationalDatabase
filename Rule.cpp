#include "Rule.h"

Rule::Rule()
{
    HeadPredicate = 0;
    predicateList = 0;
}

Rule::~Rule()
{

}

void Rule::setHeadPredicate(Scheme* inputHeadPredicate)
{
    HeadPredicate = inputHeadPredicate;
    return;
}

void Rule::setPredicateList(PredicateList* inputPredicateList)
{
    predicateList = inputPredicateList;
    return;
}

int Rule::getSize()
{
    return predicateList->getSize() + 1;
}

std::string Rule::toString()
{
    std::string out;
    out += "\n  " + HeadPredicate->toString();
    out += " :-";
    out += predicateList->toString();
    out += ".";
    return out;
}
