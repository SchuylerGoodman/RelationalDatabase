#ifndef RELATION_H_
#define RELATION_H_

#include "Tuple.h"
#include <set>

class Relation
{

  public:

    Relation();
    Relation(Scheme* inputScheme);
    ~Relation();

    Token* getID();

    Schema* getSchema();

    set<Tuple*>* getTuples();

    int getSchemaCount();

    int getTupleListSize();

    void insertTuple(ConstantList* inputConstantList);

    string toString();
    
  private:

    Token* Id;

    Schema* schema;

    set<Tuple*>* tuples;

    Schema* setSchema(IdentifierList* inputIdList);

};

#endif
