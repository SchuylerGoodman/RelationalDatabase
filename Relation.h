#ifndef RELATION_H_
#define RELATION_H_

#include "Tuple.h"
#include <set>
#include <map>

class Relation
{

  public:

    Relation();
    Relation(Scheme* inputScheme);
    Relation(const Relation& inputRelation);
    ~Relation();

    Token* getID() const;

    Schema* getSchema();

    void setSchema(Schema& inputSchema);

    set<Tuple>* getTuples();

    int getSchemaCount();

    void initTuples();

    int getTupleListSize();

    void insertTuples(ConstantList* inputConstantList);

    void insertTuple(Tuple& inputTuple);

    string toString();
    
    string tuplesToString();

    string solvedQueryToString(vector<Token>& inputTokens);

    Relation select(vector<Token>& inputTokens);

    Relation rename(Query* inputQuery);

    void renameSchemaAt(int index, Token& inputToken);
    
    Relation project(vector<Token>& inputTokens);


//    void recursiveProject(set<Tuple>* inputTuples, vector< pair<Token, Token> >* inputTokens, int inputIndex, Domain* inputDomain);
    
  private:

    Token* Id;

    Schema* schema;

    set<Tuple>* tuples;

    Schema* setSchema(IdentifierList* inputIdList);

};

#endif
