#ifndef TUPLE_H_
#define TUPLE_H_

#include "Schema.h"

typedef pair<Token*, Token*> tuplePair;

class Tuple
{

  public:

    Tuple();
    Tuple(tuplePair tpair);
    ~Tuple();
    Tuple(Schema* inputSchema, ConstantList* inputConstantList);
    
    friend bool operator<(const Tuple& t1, const Tuple& t2);

    vector<tuplePair*>* getPairs();

    string toString();

  private:

    vector<tuplePair*>* pairs; // a vector with schemaID-constant pairs

};

#endif
