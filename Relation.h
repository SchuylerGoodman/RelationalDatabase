#ifndef RELATION_H_
#define RELATION_H_

#include "Tuple.h"
#include <set>
#include <map>

vector<Token> combineTokenVectors(vector<Token>& first, vector<Token>& second);

vector<Token> removeStrings(vector<Token>& inputVector);

vector<int> getIDsFromTokenVector(vector<Token>& inputVector);

class Relation
{

  public:

    Relation();
    Relation(Scheme* inputScheme);
    Relation(const Relation& inputRelation);
    ~Relation();

    Token* getID() const;

    Schema* getSchema() const;

    set<Tuple>* getTuples() const;

    int getSchemaCount();

    void initTuples();

    int getTupleListSize();

    void insertTuples(ConstantList* inputConstantList);

    void insertTuple(Tuple& inputTuple);

    void setTuples(set<Tuple>* inputTuples);

    string toString();
    
    string tuplesToString();

    string solvedQueryToString(vector<Token>& inputTokens);

    void setSchemaFromTuples();

    Relation select(vector<Token>& inputTokens);

    Relation rename(pair<vector<Token>, vector<Token> >& ruleParameters, Relation& targetRelation);

    Relation project(vector<Token>& inputTokens, vector<Token>* opTokens);

    Relation Join(pair<vector<Token>, vector<Token> >& pair, Relation* nextRelation);

  private:

    Token* Id;

    Schema* schema;

    set<Tuple>* tuples;

    Schema* setSchema(IdentifierList* inputIdList);

    void setSchema(Schema& inputSchema);

    Relation CartesianCrossProduct(pair<vector<Token>, vector<Token> >& pair, Relation& inputRelation);

};

#endif
