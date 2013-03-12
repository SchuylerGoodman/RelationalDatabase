#ifndef QUERYLIST_H_
#define QUERYLIST_H_

#include "Query.h"

class QueryList
{

  public:

    QueryList();
    ~QueryList();

    void setQuery(Query* inputQuery);

    void addQuery(Query* inputQuery);

    int getSize();

    std::string toString();

  private:

    Query* firstQuery;

    vector<Query*> queryList;

    int listSize;

};

#endif
