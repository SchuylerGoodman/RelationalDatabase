#include "Domain.h"

Domain::Domain()
{
    listSize = 0;
}

Domain::~Domain()
{

}

void Domain::addString(std::string inString)
{
    strings.insert(inString);
    return;
}

int Domain::getSize()
{
    return strings.size();
}

std::string Domain::toString()
{
    std::string out;
    set<std::string>::iterator it;
    for(it = strings.begin(); it != strings.end(); ++it)
    {
        out += "\n  " + *it;
    }
    return out;
}
