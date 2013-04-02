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

    Relation workThatRelation(Relation& inputRelation, Query* inputQuery);

    vector<Relation*>* relations;

    Relation* getRelation(Scheme* inputScheme);

    Relation* findRelation(Token relationID);

    void insertTuple(Fact* inputFact);

    string solveRules();

    string answerQuery(Query* inputQuery); 

    vector<Scheme*>* schemes;

    vector<Fact*>* facts;

    vector<Rule*>* rules;

    vector<Query*>* queries;

};

#endif
