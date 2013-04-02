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

Scheme* Rule::getHeadPredicate()
{
    return HeadPredicate;
}

PredicateList* Rule::getPredicateList()
{
    return predicateList;
}

vector<Token> Rule::getParametersAt(int index)
{
    vector<Token> newVec;
    vector<Parameter*>* parameters = (*predicateList->getPredicates())[index]->getParameterList()->getParameters();
    for(int i = 0; i < parameters->size(); i++)
    {
        newVec.push_back((*(*parameters)[i]->getParameterToken()));
    }
    return newVec;
}

Token Rule::getParameterIDAt(int index)
{
    Token newToken = (*(*predicateList->getPredicates())[index]->getPredicateID());
    return newToken;
}
