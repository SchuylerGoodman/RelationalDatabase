#ifndef PARAMETER_H_
#define PARAMETER_H_

#include "Lex.h"

class Parameter
{

  public:

    Parameter();
    ~Parameter();

    struct Expression
    {
        
        Parameter* param1;
        
        Parameter* param2;

        Token* operata;

        Expression() {param1 = 0; param2 = 0; operata = 0;};

    };

    void newExpression();

    void setToken(Token* inputToken);

    void setExParam(Parameter* inputParameter);

    bool setExToken(Token* inputToken);

    std::string toString();

    std::string expressionToString();

  private:

    Token* token;
    
    Expression* expression;

};


#endif
