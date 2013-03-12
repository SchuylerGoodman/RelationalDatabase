#include "QueryList.h"

QueryList::QueryList()
{
    firstQuery = 0;
    listSize = 0;
}

QueryList::~QueryList()
{

}

void QueryList::setQuery(Query* inputQuery)
{
    firstQuery = inputQuery;
    return;
}

void QueryList::addQuery(Query* inputQuery)
{
    queryList.push_back(inputQuery);
    ++listSize;
    return;
}

int QueryList::getSize()
{
    return listSize;
}

std::string QueryList::toString()
{
    std::string out;
    out += "\n  " + firstQuery->toString();
    for(int i = 0; i < listSize; ++i)
    {
        out += "\n  " + queryList[i]->toString();
    }
    return out;
}
