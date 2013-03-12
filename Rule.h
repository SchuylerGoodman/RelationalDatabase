#ifndef RULE_H_
#define RULE_H_

#include "PredicateList.h"
#include "Scheme.h"

class Rule
{

  public:

    Rule();
    ~Rule();

    void setHeadPredicate(Scheme* inputHeadPredicate);

    void setPredicateList(PredicateList* inputPredicateList);

    int getSize();

    std::string toString();

  private:

    Scheme* HeadPredicate;

    PredicateList* predicateList;

};

#endif
