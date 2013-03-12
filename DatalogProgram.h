#ifndef DATALOG_PROGRAM_H_
#define DATALOG_PROGRAM_H_

#include "SchemesList.h"
#include "FactsList.h"
#include "RulesList.h"
#include "QueryList.h"
#include "Domain.h"
#include <iostream>
#include <sstream>

class DatalogProgram
{
  public:
    DatalogProgram();
    ~DatalogProgram();

    void setSchemesList(SchemesList* schemeslist);

    SchemesList* getSchemesList();
    
    void setFactsList(FactsList* factslist);

    FactsList* getFactsList();

    void setRulesList(RulesList* ruleslist);

    RulesList* getRulesList();

    void setQueryList(QueryList* querylist);

    QueryList* getQueryList();

    void setDomain(Domain* domain);

    Domain* getDomain();

    std::string toString();
  private:
    SchemesList* slist;
    FactsList* flist;
    RulesList* rlist;
    QueryList* qlist;
    Domain* dman;

};

#endif
