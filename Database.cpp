#include "Database.h"

Database::Database(DatalogProgram* dprog)
{
    schemes = dprog->getSchemesList()->getSchemes();
    facts = dprog->getFactsList()->getFacts();
    rules = dprog->getRulesList()->getRules();
    queries = dprog->getQueryList()->getQueries();

    relations = new vector<Relation*>();

//Make Relations From Schemes
    for(int i = 0; i < schemes->size(); i++)
    {
        relations->push_back(getNewRelation((*schemes)[i]));
    }

//Insert Tuples From Facts
    for(int i = 0; i < facts->size(); i++)
    {
        insertTuple((*facts)[i]);
    }

//Populate Tuples from Rules TODO
    /*if(rules->size() > 0)
    {
        cout << solveRules() + "\n";
    }*/

    //string getOUT;
    depends = new graph(this);
//Answer Queries
    for(int i = 0; i < queries->size(); i++)
    {
        string out;
        out += (*queries)[i]->toString();
        out += solveQuery((*queries)[i]) + "\n";/*
        out += answerQuery((*queries)[i]) + "\n";
        vector<graphnode*>* dfsTree = depends->buildDFS((*queries)[i]);
        if(dfsTree != 0)
        {
            for(int j = 0; j < dfsTree->size(); j++)
            {
                if(j > 0)
                {
                    getOUT += ", ";
                }
                getOUT += (*dfsTree)[j]->simpleToString();
            }
            getOUT += "\n";
        }*/
        cout << out;
    }


    //cout << depends->toString() << "\n";
    //cout << "TREES" << endl << getOUT;
}

Database::~Database()
{
}

vector<Relation*>* Database::getRelations()
{
    return relations;
}

string Database::toString()
{
    string out;
    for(int i = 0; i < relations->size(); i++)
    {
        out += (*relations)[i]->toString();
    }
    return out;
}

int Database::getRulesListSize()
{
    return rules->size();
}

Rule* Database::getRuleAt(int& index)
{
    if(index > rules->size())
    {
        return 0;
    }
    return (*rules)[index];
}

Relation Database::workThatRelation(Relation& inputRelation, Query* inputQuery)
{
    vector<Token> queryTokens;
    vector<Parameter*>* plist = inputQuery->getPredicate()->getParameterList()->getParameters();
    for(int i = 0; i < plist->size(); i++)
    {
        queryTokens.push_back((*(*plist)[i]->getParameterToken()));
    }
   
    Relation R1 = inputRelation.select(queryTokens);

    Relation R2 = R1.project(queryTokens, 0);
    return R2;
}

Relation* Database::getNewRelation(Scheme* inputScheme)
{
    Relation* relation = new Relation(inputScheme);
    return relation;
}

Relation* Database::findRelation(Token* relationID)
{
    if(relationID == 0)
    {
        return 0;
    }
    else
    {
        for(int i = 0; i < relations->size(); i++)
        {
            if((*(*relations)[i]->getID()).getTokensValue() == relationID->getTokensValue())
            {
                Relation* outRelation = (*relations)[i];
                return outRelation;
            }
        }
        throw("This relation does not exist");
    }
}

void Database::setRelation(Relation* inputRelation)
{
    Token* relationID = inputRelation->getID();
    for(int i = 0; i < relations->size(); i++)
    {
        if((*(*relations)[i]->getID()).getTokensValue() == relationID->getTokensValue())
        {
            (*relations)[i] = inputRelation;
            return;
        }
    }
    throw("Relation with ID=" + relationID->getTokensValue() + " not found in database");
}

void Database::insertTuple(Fact* inputFact)
{
    string tokenValue = "";
    int counter = 0;
    //loop to find relation that corresponds to this fact
    while((*relations)[counter] != 0 && inputFact->getFactID()->getTokensValue() != (*relations)[counter]->getID()->getTokensValue())
    {
        ++counter;
    }
    if((*relations)[counter] == 0) //if the fact doesn't correspond to a relation (shouldn't happen, according to the specifications)
    {
        throw("Error in Database.cpp::insertTuple");
    }
    else //insert a tuple a the selected relation
    {
        (*relations)[counter]->insertTuples(inputFact->getConstantList());
    }
}

string Database::solveQuery(Query* inputQuery)
{
    string out;
    if(rules->size() > 0)
    {
      vector<graphnode*>* dfsTree = depends->buildDFS(inputQuery);
      if(dfsTree != 0) // if query has dependencies
      {
          for(int i = 0; i < dfsTree->size(); i++) // for all in topsort
          {
              if((*dfsTree)[i]->lfp() == false) // if no cycle here
              {
                  for(int j = 0; j < rules->size(); j++) // for every rule
                  {
                      if((*dfsTree)[i]->getRelation()->getID()->getTokensValue() == (*rules)[j]->getHeadPredicateID()->getTokensValue())//rfind
                      {
                          solveRule((*rules)[j]); // solve it!
                      }
                  }
              }
              else // if cycle starts here
              {
                  int count = i; // for every node in the cycle, use the least fixed point algorithm
                  while(count < dfsTree->size() && (*dfsTree)[count]->lfp() != false) // in topsort, and lfp = true
                  {
                      ++count;
                  }
                  solveRules(dfsTree, i, count);
                  i = count - 1; // move i ahead as necessary
              }
          }
      }
    }
    out += answerQuery(inputQuery); // answer the query
    return out;
}

//rules

void Database::solveRule(Rule* inputRule)
{
    Relation firstRelation = (*findRelation(inputRule->getParameterIDAt(0)));
    vector<Token> firstParams = (*inputRule->getParametersAt(0));
    pair<vector<Token>, vector<Token> > newPair(firstParams, vector<Token>());

    for(int j = 0; j < inputRule->getSize(); j++)
    {
        Relation* secondRelation = findRelation(inputRule->getParameterIDAt(j + 1));
        vector<Token>* secondParams = inputRule->getParametersAt(j + 1);
        if(secondParams != 0)
        {
            newPair.second = (*secondParams);
        }
        Relation newRelation(firstRelation.Join(newPair, secondRelation));
        firstRelation = newRelation;
    }

    Relation* headRelation = findRelation(inputRule->getHeadPredicateID());
    newPair.second = newPair.first;
    newPair.first = inputRule->getHeadPredicateParameters();
    Relation* afterUnion = new Relation(headRelation->Union(newPair, firstRelation));
    Relation* deleteRelation = headRelation;
    setRelation(afterUnion);
//    delete deleteRelation;
    return;
}

void Database::solveRules(vector<graphnode*>* toppity, int& begin, int& end)
{
    int preCount = 0;

    int times = 0;
    string out;
    vector<Rule*>* unruly = new vector<Rule*>();
    for(int i = begin; i < end; i++)
    {
        for(int j = 0; j < rules->size(); j++)
        {
            if((*toppity)[i]->getRelation()->getID()->getTokensValue() == (*rules)[j]->getHeadPredicateID()->getTokensValue())
            {
                unruly->push_back((*rules)[j]);
            }
        }
    }
    int postCount = getTupleCount(unruly);

    do
    {
        preCount = getTupleCount(unruly);
        for(int i = 0; i < unruly->size(); i++)
        {
            solveRule((*unruly)[i]);
        }
        postCount = getTupleCount(unruly);
        ++times;
    }while(preCount != postCount);
    stringstream tout; tout << times;
    out = "Schemes populated after " + tout.str() + " passes through the Rules.";
    delete unruly;
    return;
}
    

string Database::answerQuery(Query* inputQuery)
{
    string out;
    Relation good_relation;
    Token* toke = inputQuery->getQueryID();

    vector<Token> queryTokens; // Get Tokens from Query ParameterList
    vector<Parameter*>* plist = inputQuery->getPredicate()->getParameterList()->getParameters();
    for(int i = 0; i < plist->size(); i++)
    {
        queryTokens.push_back((*(*plist)[i]->getParameterToken()));
    }

    for(int i = 0; i < relations->size(); i++)
    {
        if(toke->getTokensValue() == (*relations)[i]->getID()->getTokensValue())
        {
            good_relation = workThatRelation( (*(*relations)[i]), inputQuery);
        }
    }
    if(good_relation.getTupleListSize() == 0)
    {
        out += " No";
    }
    else
    {
        stringstream ssout;
        ssout << good_relation.getTupleListSize();
        out += " Yes(" + ssout.str() + ")";
        out += good_relation.solvedQueryToString(queryTokens);
    }
    return out;
}

int Database::getTupleCount(vector<Rule*>* thisTotallyRules)
{
    int count = 0;
    for(int i = 0; i < thisTotallyRules->size(); i++)
    {
        Relation* thisRelationRules = this->findRelation((*thisTotallyRules)[i]->getHeadPredicateID());
        count += thisRelationRules->getTupleListSize();
    }
    return count;
}

int main(int argc, char* argv[])
{
    int* counter = new int(0);
    Lex lex(argv[1]);
    vector<Token*>* raw_vector = lex.tokens;
    Parser* parser = new Parser(parser->MrVectorCleaner(raw_vector), counter);
    DatalogProgram* datalogProgram = parser->parseDatalogProgram();
    if(parser->hazFailed())
    {
        cout << "Failure!" << endl;
        cout << "  " << parser->getFailToken()->toString();
    }
    else
    {
        Database* dbase = new Database(datalogProgram);
    }
    

    return 0;
}
