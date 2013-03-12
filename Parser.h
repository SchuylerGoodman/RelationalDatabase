#ifndef PARSER_H_
#define PARSER_H_

#include "DatalogProgram.h"
#include "Lex.h"
#include <iostream>

class Parser
{
  public:

    Parser();

    Parser(vector<Token*>* inputTokens, int* inputCount);

    ~Parser();

    DatalogProgram* parseDatalogProgram();

    Token* getFailToken();

    bool hazFailed();

  private:

    TokenType getTokenType();

    SchemesList* parseSchemesList(int* newCount);

    Scheme* parseScheme(int* newCount);

    IdentifierList* parseIdentifierList(int* newCount);

    FactsList* parseFactsList(int* newCount, Domain* dman);

    Fact* parseFact(int* newCount, Domain* dman);

    ConstantList* parseConstantList(int* newCount, Domain* dman);

    RulesList* parseRulesList(int* newCount, Domain* dman);

    Rule* parseRule(int* newCount, Domain* dman);

    PredicateList* parsePredicateList(int* newCount, Domain* dman);

    Predicate* parsePredicate(int* newCount, Domain* dman);

    ParameterList* parseParameterList(int* newCount, Domain* dman);

    Parameter* parseParameter(int* newCount, Domain* dman);

    void parseExpression(Parameter* param, int* newCount, Domain* dman);
    QueryList* parseQueryList(int* newCount, Domain* dman);

    Query* parseQuery(int* newCount, Domain* dman);

    //etc
    
//+++++++++++++++++++Data Members+++++++++++++++++++
    bool failure;
    
    Token* fail;

    vector<Token*>* tokens;

    int* count;

};

#endif
