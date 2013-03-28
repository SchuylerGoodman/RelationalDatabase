#include "Relation.h"

Relation::Relation()
{
    tuples = 0;
    schema = 0;
    Id = 0;
}

Relation::Relation(Scheme* inputScheme)
{

    tuples = new set<Tuple>();

    Id = inputScheme->getSchemeID(); //set main ID to Scheme ID

    schema = setSchema(inputScheme->getIDList()); //set Schema to Scheme ID List

}

Relation::Relation(const Relation& inputRelation)
{

    Id = new Token(*inputRelation.getID());
    schema = 0;
}

Relation::~Relation()
{
}

Token* Relation::getID() const
{
    return Id;
}

Schema* Relation::getSchema()
{
    return schema;
}

set<Tuple>* Relation::getTuples()
{
    return tuples;
}

int Relation::getSchemaCount()
{
    return schema->getListSize();
}

void Relation::initTuples()
{
    tuples = new set<Tuple>();
}

int Relation::getTupleListSize()
{
    return tuples->size();
}

Schema* Relation::setSchema(IdentifierList* inputIdList)
{
    Schema* outSchema = new Schema(inputIdList);

    return outSchema;
}

void Relation::insertTuples(ConstantList* inputConstantList)
{
    Tuple newTuple(schema,inputConstantList);
    tuples->insert(newTuple);
}

void Relation::insertTuple(Tuple& inputTuple)
{
    tuples->insert(inputTuple);
    return;
}

string Relation::toString()
{
    string out = "";
    out += Id->getTokensValue();
    out += ":";
    out += schema->toString() + "\n";
    for(set<Tuple>::iterator it = tuples->begin(); it != tuples->end(); it++)
    {
        for(int i = 0; i < Id->getTokensValue().length(); i++)
        {
            out += " ";
        }
        Tuple thisTuple = (*it);
        out += "  " + thisTuple.toString() + "\n";
    }
    return out;
}

string Relation::tuplesToString()
{
    string out;
    for(set<Tuple>::iterator it = tuples->begin(); it != tuples->end(); it++)
    {
        Tuple thisTuple = (*it);
        if(thisTuple.toString() != "")
        {
            out += "\n";
        }
        out += "  " + thisTuple.toString();
    }
    return out;
}

string Relation::solvedQueryToString(vector<Token>& inputTokens)
{
    string out;
    vector<std::pair<Token, vector<int> > > myMap;
    for(int i = 0; i < inputTokens.size(); i++)
    {
        bool inserted = false;
        for(int j = 0; j < myMap.size(); j++)
        {
            if(myMap[j].first.getTokensValue() == inputTokens[i].getTokensValue())
            {
                myMap[j].second.push_back(i);
                inserted = true;
            }
        }
        if(!inserted)
        { 
            vector<int> newVec;
            newVec.push_back(i);
            myMap.push_back(pair<Token, vector<int> >(inputTokens[i], newVec) );
        }
    }

    for(set<Tuple>::iterator it = tuples->begin(); it != tuples->end(); it++)
    {
        int firstInMapVector = 0;
        Tuple thisTuple = (*it);
        if(thisTuple.toString() != "")
        {
            out += "\n  ";
        }
        for(int i = 0; i < myMap.size(); i++)
        {
            if(myMap[i].first.getTokenType() == ID)
            {
                out += myMap[i].first.getTokensValue() + "=";
                out += thisTuple.getTokenFromPairAt(myMap[i].second[firstInMapVector]).getTokensValue();
                if(i + 1 != myMap.size())
                {
                    out += ", ";
                }
            }
        }
    }
    return out;
}

void Relation::setSchema(Schema& inputSchema)
{
    if(!schema)
    {
        schema = new Schema(inputSchema);
    }
    else
    {
        (*schema) = inputSchema;
    }
    return;
}

Relation Relation::select(vector<Token>& inputTokens)
{
    Relation newRelation(*this);
    newRelation.setSchema(*schema); 
    newRelation.initTuples();
    map<Token, vector<int> > myMap;
    
    for(int i = 0; i < inputTokens.size(); i++)
    {
        if(inputTokens[i].getTokenType() == ID)
        {
            bool inserted = false;
            for(map<Token, vector<int> >::iterator it = myMap.begin(); it != myMap.end(); it++)
            {
                if(it->first.getTokensValue() == inputTokens[i].getTokensValue())
                {
                    it->second.push_back(i);
                    inserted = true;
                }
            }
            if(!inserted)
            { 
                vector<int> newVec;
                newVec.push_back(i);
                myMap.insert(pair<Token, vector<int> >(inputTokens[i], newVec) );
            }
        }
    }

    //Goes through all Tuples in THIS relation, checks if all query strings match, and adds matching tuples to the returned relation
    for(set<Tuple>::iterator it = tuples->begin(); it != tuples->end(); it++) //for all tuples in THIS
    {
        bool isTrue = true;
        Tuple tempTuple = (*it);
        Tuple thisTuple = tempTuple;
        for(int j = 0; j < thisTuple.getPairVectorSize(); j++) //for all pairs in this tuple
        {
            for(int i = 0; i < inputTokens.size(); i++) //for all parameters in the query
            {
                if(inputTokens[i].getTokenType() == STRING && j == i) //if this parameter is the placeholder string
                {
                    if(inputTokens[i].getTokensValue() != thisTuple.getTokenFromPairAt(j).getTokensValue()) //if the values don't match
                    {
                        isTrue = false; //do not add to the new relation
                    }
                }
                else
                {
                    for(map<Token, vector<int> >::iterator mit = myMap.begin(); mit != myMap.end(); mit++)
                    {
                        for(int k = 0; k < thisTuple.getPairVectorSize(); k++)
                        {
                            for(int h = 0; h < mit->second.size(); h++)
                            {
                                if(k == mit->second[h])
                                {
                                    for(int n = 0; n < mit->second.size(); n++)
                                    {
                                        if(thisTuple.getPairs()[k].second.getTokensValue() != thisTuple.getPairs()[mit->second[n]].second.getTokensValue())
                                        {
                                            isTrue = false;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if(isTrue) //otherwise add the tuple to the new relation
        {
            newRelation.insertTuple(thisTuple);
        }
    }
    return newRelation;
}

Relation Relation::rename(Query* inputQuery)
{
    Relation newRelation(*this);
    newRelation.setSchema(*schema);
    newRelation.initTuples();

    vector<Parameter*>* plist = inputQuery->getPredicate()->getParameterList()->getParameters();

    for(set<Tuple>::iterator it = tuples->begin(); it != tuples->end(); it++) // for all original tuples
    {
        Tuple thisTuple = (*it); // copy this tuple
        for(int i = 0; i < plist->size(); i++) // for every parameter in the query
        {
            if((*plist)[i]->getParameterToken()->getTokenType() == ID) // if the parameter is an ID
            {
                thisTuple.renameTokenSchemaAt(i, (*(*plist)[i]->getParameterToken())); // rename the copied tuples schema
                newRelation.renameSchemaAt(i, (*(*plist)[i]->getParameterToken()));
            }
        }
        newRelation.insertTuple(thisTuple); // insert copied tuple into new relation tuple set
    }
    return newRelation;
}

void Relation::renameSchemaAt(int index, Token& inputToken)
{
    schema->renameTokenAt(index, inputToken);
    return;
}

Relation Relation::project(vector<Token>& inputTokens)
{
    Relation newRelation = (*this);
    Schema newSchema(*schema);
    newRelation.initTuples();
    bool SchemaFull = true;

    for(set<Tuple>::iterator it = tuples->begin(); it != tuples->end(); it++) // for all the old tuples
    {
        Tuple newTuple = (*it); // copy this tuple
        newTuple.removePairWithout(inputTokens); // remove pairs that don't fit projection parameters
        newRelation.insertTuple(newTuple);
    }
    return newRelation;
}
/*
void Relation::recursiveProject(set<Tuple>* inputTuples, vector< pair<Token, Token> >* inputTokens, int inputIndex, Domain* inputDomain)
{
    for(set<std::string>::iterator dIt = inputDomain->getStrings().begin(); dIt != inputDomain->getStrings().end(); dIt++)
    {
        (*inputTokens)[inputIndex].second.setTokenValue((*dIt));
        if(inputIndex == inputTokens->size() - 1)
        {
            for(set<Tuple>::iterator it = tuples->begin(); it != tuples->end(); it++)
            {
                bool insert = true;
                Tuple newTuple = (*it);
                for(int j = 0; j < inputTokens->size(); j++)
                {
                    for(int i = 0; i < newTuple.getPairs().size(); i++)
                    {
                        if(newTuple.getPairs()[i].first.getTokensValue() != (*inputTokens)[j].first.getTokensValue())
                        {
                            insert = false;
                        }
                        else 
                        {
                            if(newTuple.getPairs()[i].second.getTokensValue() != (*inputTokens)[j].second.getTokensValue())
                            {
                                insert = false;
                            }
                        }
                    }
                }
                if(insert)
                {
                    inputTuples->insert(newTuple);
                }
            }
        }           
        else
        {
            recursiveProject(inputTuples, inputTokens, inputIndex + 1, inputDomain);
        }
    }                   
    return;
}*/
