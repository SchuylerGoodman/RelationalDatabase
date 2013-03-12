#ifndef FACTS_LIST_H_
#define FACTS_LIST_H_

#include "Fact.h"

class FactsList
{

  public:
    
    FactsList();
    ~FactsList();

    void addFact(Fact* inputFact);

    int getSize();

    std::string toString();

  private:

    vector<Fact*> facts;

    int listSize;

};


#endif
