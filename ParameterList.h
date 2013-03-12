#ifndef PARAMETERLIST_H_
#define PARAMETERLIST_H_

#include "Parameter.h"

class ParameterList
{

  public:

    ParameterList();
    ~ParameterList();

    void setParam(Parameter* inputParameter);

    void addParam(Parameter* inputParameter);

    int getSize();

    std::string toString();

  private:

    Parameter* mainParam;

    vector<Parameter*> parameterList;

    int listSize;

};


#endif
