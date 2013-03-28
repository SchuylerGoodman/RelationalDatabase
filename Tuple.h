#ifndef TUPLE_H_
#define TUPLE_H_

#include "Schema.h"

typedef pair<Token, Token> tuplePair;

class Tuple
{

  public:

    Tuple();
    ~Tuple();
    Tuple(Schema* inputSchema, ConstantList* inputConstantList);
    Tuple(const Tuple& inputTuple);

//    Tuple* makeNewTuple();
    
    tuplePair getTuplePairAt(int index) const;

    vector<tuplePair> getPairs() const;

    void setPairs(vector<tuplePair> inputPairs);

    Token getTokenFromPairAt(int index);

    void renameTokenSchemaAt(int index, Token& inputToken);

    void removePairWithout(set< pair<Token, Token> >* inputTokens);

    void removePairAt(int index);

    int getPairVectorSize() const;

    string toString();

    friend bool operator<(const Tuple& t1, const Tuple& t2);

  private:

    vector<tuplePair> pairs; // a vector with schemaID-constant pairs

};

#endif
