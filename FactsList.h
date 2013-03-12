#ifndef FACTS_LIST_H_
#define FACTS_LIST_H_

#include "Fact.h"
#include <iostream>

class FactsList
{

  public:
    
    FactsList();
    ~FactsList();

    void addFact(Fact* inputFact);

    int getSize();

    std::string toString();

    vector<Fact*>* getFacts();

  private:

    vector<Fact*> facts;

    int listSize;

};


#endif
