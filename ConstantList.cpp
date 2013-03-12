#include "ConstantList.h"

ConstantList::ConstantList()
{
    listSize = 0;
    BigDaddyString = 0;
}

ConstantList::~ConstantList()
{

}

void ConstantList::setString(Token* inputString)
{
    BigDaddyString = inputString;
    return;
}

void ConstantList::addString(Token* inputString)
{
    StringList.push_back(inputString);
    ++listSize;
    return;
}

int ConstantList::getSize()
{
    return listSize;
}

std::string ConstantList::toString()
{
    std::string out;
    out += BigDaddyString->getTokensValue();
    for(int i = 0; i < listSize; ++i)
    {
        out += "," + StringList[i]->getTokensValue();
    }
    return out;
}
