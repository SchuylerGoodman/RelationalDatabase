#include "ParameterList.h"

ParameterList::ParameterList()
{
    mainParam = 0;
    listSize = 0;
}

ParameterList::~ParameterList()
{

}

void ParameterList::setParam(Parameter* inputParameter)
{
    mainParam = inputParameter;
    return;
}

void ParameterList::addParam(Parameter* inputParameter)
{
    parameterList.push_back(inputParameter);
    ++listSize;
    return;
}

int ParameterList::getSize()
{
    return listSize;
}

std::string ParameterList::toString()
{
    std::string out;
    out += mainParam->toString();
    for(int i = 0; i < listSize; ++i)
    {
        out += "," + parameterList[i]->toString();
    }
    return out;
}

vector<Parameter*>* ParameterList::getParameters()
{
    vector<Parameter*>* params = new vector<Parameter*>();
    params->push_back(mainParam);
    for(int i = 0; i < listSize; i++)
    {
        params->push_back(parameterList[i]);
    }
    return params;
}
