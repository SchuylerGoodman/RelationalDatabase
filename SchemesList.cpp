#include "SchemesList.h"
#include <iostream>

SchemesList::SchemesList()
{
    scheme = 0;
    listSize = 0;
}

SchemesList::~SchemesList()
{
    for(int i = 0; i < listSize; ++i)
    {
        delete[] schemes[i];
    }
}

void SchemesList::setScheme(Scheme* inputScheme)
{
    scheme = inputScheme;
    return;
}

void SchemesList::addScheme(Scheme* scheme)
{
    schemes.push_back(scheme);
    ++listSize;
    return;
}

int SchemesList::getSize()
{
    return listSize;
}

std::string SchemesList::toString()
{
    string out;
    out += "\n  " + scheme->toString();
    for(int i = 0; i < listSize; ++i)
    {
        out += "\n  " + schemes[i]->toString();
    }
    return out;
}
