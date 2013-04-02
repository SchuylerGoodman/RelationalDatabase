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
        relations->push_back(getRelation((*schemes)[i]));
    }

//Insert Tuples From Facts
    for(int i = 0; i < facts->size(); i++)
    {
        insertTuple((*facts)[i]);
    }

//Populate Tuples from Rules TODO
    cout << solveRules() + "\n";

//Answer Queries
    for(int i = 0; i < queries->size(); i++)
    {
        string out;
        out += (*queries)[i]->toString();
        out += answerQuery((*queries)[i]) + "\n";
        cout << out;
    }
}

Database::~Database()
{
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

Relation* Database::getRelation(Scheme* inputScheme)
{
    Relation* relation = new Relation(inputScheme);
    return relation;
}

Relation* Database::findRelation(Token relationID)
{
    for(int i = 0; i < relations->size(); i++)
    {
        if((*(*relations)[i]->getID()).getTokensValue() == relationID.getTokensValue())
        {
            Relation* outRelation = (*relations)[i];
            return outRelation;
        }
    }
    throw("Relation with ID=" + relationID.getTokensValue() + " not found in database");
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

//rules
string Database::solveRules()
{
    string out;
    for(int i = 0; i < rules->size(); i++)
    {
        if((*rules)[i]->getSize() > 1)
        {
            Relation* firstRelation = findRelation((*rules)[i]->getParameterIDAt(0));
            Relation* secondRelation = findRelation((*rules)[i]->getParameterIDAt(1));
            vector<Token> firstParams = (*rules)[i]->getParametersAt(0);
            vector<Token> secondParams = (*rules)[i]->getParametersAt(1);
            pair<vector<Token>, vector<Token> > newPair(firstParams, secondParams);
            Relation newRelation(firstRelation->Join(newPair, secondRelation));
            out += newRelation.toString() + "\n";
        }
    }
    return out;
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
