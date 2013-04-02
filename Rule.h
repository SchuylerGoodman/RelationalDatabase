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

    Scheme* getHeadPredicate();

    PredicateList* getPredicateList();

    Token getHeadPredicateID();

    vector<Token> getHeadPredicateParameters();

    vector<Token> getParametersAt(int index);

    Token getParameterIDAt(int index);

  private:

    Scheme* HeadPredicate;

    PredicateList* predicateList;

};

#endif
