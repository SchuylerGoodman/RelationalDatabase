#include "Parameter.h"

Parameter::Parameter()
{
    token = 0;
    expression = 0;
}

Parameter::~Parameter()
{

}

void Parameter::newExpression()
{
    expression = new Expression();
    return;
}

void Parameter::setToken(Token* inputToken)
{
    token = inputToken;
    return;
}

void Parameter::setExParam(Parameter* inputParameter)
{
    if(expression->param1 == 0)
    {
        expression->param1 = inputParameter;
    }
    else
    {
        expression->param2 = inputParameter;
    }
    return;
}

bool Parameter::setExToken(Token* inputToken)
{
    bool isRight = true;
    if(inputToken->getTokenType() == MULTIPLY || inputToken->getTokenType() == ADD)
    {
        expression->operata = inputToken;
    }
    else
    {
        isRight = false;
    }
    return isRight;
}

std::string Parameter::toString()
{
    std::string out;
    if(token != 0)
    {
        out += token->getTokensValue();
    }
    else if(expression != 0)
    {
        out += expressionToString();
    }
    else
    {
        throw("In Parameter.cpp: No string, ID, or Expression input before string output");
    }
    return out;
}

std::string Parameter::expressionToString()
{
    std::string out;
    out += "(";
    out += expression->param1->toString();
    out += expression->operata->getTokensValue();
    out += expression->param2->toString();
    out += ")";
    return out;
}
