#ifndef TUPLE_H_
#define TUPLE_H_

#include "Schema.h"

typedef pair<Token*, Token*> tuplePair;

class Tuple
{

  public:

    Tuple();
    ~Tuple();
    Tuple(Schema* inputSchema, ConstantList* inputConstantList);
    
    vector<tuplePair*>* getPairs();

    string toString();

    friend bool operator<(Tuple& t1, Tuple& t2);

    friend bool operator==(Tuple& t1, Tuple& t2);

  private:

    vector<tuplePair*>* pairs; // a vector with schemaID-constant pairs

};

#endif
