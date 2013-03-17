#include "Database.h"

Database::Database(DatalogProgram* dprog)
{
    vector<Scheme*>* schemes = dprog->getSchemesList()->getSchemes();
    vector<Fact*>* facts = dprog->getFactsList()->getFacts();
    //vector<Rule*>* rules = dprog->getRulesList()->getRules();
    vector<Query*>* queries = dprog->getQueryList()->getQueries();

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

//Answer Queries
    for(int i = 0; i < queries->size(); i++)
    {
        cout << answerQuery((*queries)[i]);
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

Relation* Database::getRelation(Scheme* inputScheme)
{
    Relation* relation = new Relation(inputScheme);
    return relation;
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
        (*relations)[counter]->insertTuple(inputFact->getConstantList());
    }
}

//rules

string Database::answerQuery(Query* inputQuery)
{
    string out = "I'll get to Queries when I can...\n";
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
        cout << "Success!" << endl;
        cout << datalogProgram->toString();
    }

    Database* dbase = new Database(datalogProgram);

    cout << dbase->toString();

    return 0;
}
