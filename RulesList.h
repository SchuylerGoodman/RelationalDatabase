#ifndef RULESLIST_H_
#define RULESLIST_H_

#include "Rule.h"

class RulesList
{

  public:

    RulesList();
    ~RulesList();

    void addRule(Rule* inputRule);

    int getSize();

    std::string toString();

  private:

    vector<Rule*> rulesList;

    int listSize;

};

#endif
