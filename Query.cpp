#include "Query.h"

Query::Query()
{
    predicate = 0;
}

Query::~Query()
{

}

void Query::setPredicate(Predicate* inputPredicate)
{
    predicate = inputPredicate;
    return;
}

int Query::getParamListSize()
{
    return predicate->getSize();
}

std::string Query::toString()
{
    std::string out;
    out += predicate->toString();
    out += "?";
    return out;
}

Predicate* Query::getPredicate()
{
    return predicate;
}

Token* Query::getQueryID()
{
    return predicate->getPredicateID();
}
