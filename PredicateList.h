#ifndef PREDICATELIST_H_
#define PREDICATELIST_H_

#include "Predicate.h"

class PredicateList
{

  public:

    PredicateList();
    ~PredicateList();

    void setPredicate(Predicate* inputPredicate);

    void addPredicate(Predicate* inputPredicate);

    int getSize();

    std::string toString();

  private:

    Predicate* predicate;

    vector<Predicate*> predicateList;

    int listSize;

};

#endif
