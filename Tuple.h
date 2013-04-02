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
    Tuple(Tuple& inputTuple, Schema& inputSchema);

    Tuple removeDuplicates();
    
    tuplePair getTuplePairAt(int index) const;

    vector<tuplePair> getPairs() const;

    void setPairs(vector<tuplePair> inputPairs);

    Token getTokenFromPairAt(int index);

    void renameTokenSchemaAt(int index, Token& inputToken);

    void removePairWithout(vector<Token>& inputTokens);

    void removePairAt(int index);

    int getPairVectorSize() const;

    Tuple combineTuples(Tuple& secondTuple);

    string toString();

    Token operator[](const int& inputInt) const;

    friend bool operator<(const Tuple& t1, const Tuple& t2);

  private:

    vector<tuplePair> pairs; // a vector with schemaID-constant pairs
};

#endif
