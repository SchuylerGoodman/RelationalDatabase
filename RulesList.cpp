#include "RulesList.h"

RulesList::RulesList()
{
    listSize = 0;
}

RulesList::~RulesList()
{

}

void RulesList::addRule(Rule* inputRule)
{
    rulesList.push_back(inputRule);
    ++listSize;
    return;
}

int RulesList::getSize()
{
    return listSize;
}

std::string RulesList::toString()
{
    std::string out;
    for(int i = 0; i < listSize; ++i)
    {
        out += rulesList[i]->toString();
    }
    return out;
}
