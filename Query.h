#ifndef QUERY_H_
#define QUERY_H_

#include "Predicate.h"

class Query
{

  public:

    Query();
    ~Query();

    void setPredicate(Predicate* inputPredicate);

    int getParamListSize();

    std::string toString();

    Predicate* getPredicate();

    Token* getQueryID();

  private:
      
    Predicate* predicate;

};

#endif
