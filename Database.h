#ifndef DATABASE_H_
#define DATABASE_H_

#include "Relation.h"

class graphnode;
class graph;
class Database
{

  public:
    
    Database(DatalogProgram* dprog);

    ~Database();

    Relation* findRelation(Token* relationID);

    vector<Relation*>* getRelations();

    string toString();
    
    int getRulesListSize();

    Rule* getRuleAt(int& index);

  private:

    Relation workThatRelation(Relation& inputRelation, Query* inputQuery);

    vector<Relation*>* relations;

    Relation* getNewRelation(Scheme* inputScheme);

    void setRelation(Relation* inputRelation);

    void insertTuple(Fact* inputFact);

    string solveQuery(Query* inputQuery);

    void solveRule(Rule* inputRule);

    void solveRules(vector<graphnode*>* toppity, int& begin, int& end);

    string answerQuery(Query* inputQuery); 

    int getTupleCount(vector<Rule*>* thisTotallyRules);

    vector<Scheme*>* schemes;

    vector<Fact*>* facts;

    vector<Rule*>* rules;

    vector<Query*>* queries;

    graph* depends;

};

class graphnode
{
  public:

    graphnode();
    graphnode(Relation* inputRelation);
    ~graphnode();

    void addEdge(graphnode* inGraphnode);

    void setPostorder(int& po);

    int getPostorder();

    graphnode* operator[](const int& index) const;

    int getEdgeNumber();

    Relation* getRelation();

    string toString(); //Returns IDs of all dependencies of this node, separated by commas
    string simpleToString(); //Returns only the ID of the relation

    bool find(graphnode* searchForTHIS);

    int recursiveDFS(int po, vector<graphnode*>* topsyTurvy);

    bool seen();

    void reset();

    bool lfp();

    void setLFP_true();

  private:

    vector<graphnode*> connections;
    Relation* relation;
    int postorder;
    bool visited;
    bool leastFixedPoint;

};

class graph
{
  public:

    graph();
    graph(Database* inputDatabase);
    ~graph();

    vector<graphnode*>* buildDFS(Query* inputQuery);

    string toString();

  private:

    void reset();

    void cycleDetect(vector<graphnode*>* tippity);

    map<Token, graphnode*> graphMap;

};

#endif
