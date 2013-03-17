#ifndef DATABASE_H_
#define DATABASE_H_

#include "Relation.h"

class Database
{

  public:
    
    Database(DatalogProgram* dprog);

    ~Database();

    string toString();

  private:

    vector<Relation*>* relations;

    Relation* getRelation(Scheme* inputScheme);

    void insertTuple(Fact* inputFact);

    //populate tuples from rules TODO

    string answerQuery(Query* inputQuery); 

};

#endif
