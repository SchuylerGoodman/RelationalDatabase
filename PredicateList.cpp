#include "PredicateList.h"

PredicateList::PredicateList()
{
    predicate = 0;
    listSize = 0;
}

PredicateList::~PredicateList()
{

}

void PredicateList::setPredicate(Predicate* inputPredicate)
{
    predicate = inputPredicate;
    return;
}

void PredicateList::addPredicate(Predicate* inputPredicate)
{
    predicateList.push_back(inputPredicate);
    ++listSize;
}

int PredicateList::getSize()
{
    return listSize;
}

std::string PredicateList::toString()
{
    std::string out;
    out += " " + predicate->toString();
    for(int i = 0; i < listSize; ++i)
    {
        out += "," + predicateList[i]->toString();
    }
    return out;
}
