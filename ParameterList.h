#ifndef PARAMETERLIST_H_
#define PARAMETERLIST_H_

#include "Parameter.h"
#include <iostream>

class ParameterList
{

  public:

    ParameterList();
    ~ParameterList();

    void setParam(Parameter* inputParameter);

    void addParam(Parameter* inputParameter);

    int getSize();

    std::string toString();

    vector<Parameter*>* getParameters();

  private:

    Parameter* mainParam;

    vector<Parameter*> parameterList;

    int listSize;

};


#endif
