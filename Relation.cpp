#include "Relation.h"

vector<Token> combineTokenVectors(vector<Token>& first, vector<Token>& second)
{
    vector<Token> newVec;
    for(int i = 0; i < first.size(); i++)
    {
        bool insert = true;
        for(int j = 0; j < newVec.size(); j++)
        {
            if(first[i].getTokensValue() == newVec[j].getTokensValue())
            {
                insert = false;
            }
        }
        if(insert && first[i].getTokenType() == ID)
        {
            newVec.push_back(Token(first[i]));
        }
    }
    for(int i = 0; i < second.size(); i++)
    {
        bool insert = true;
        for(int j = 0; j < newVec.size(); j++)
        {
            if(second[i].getTokensValue() == newVec[j].getTokensValue())
            {
                insert = false;
            }
        }
        if(insert && second[i].getTokenType() == ID)
        {
            newVec.push_back(Token(second[i]));
        }
    } 
    return newVec;
}

vector<Token> removeStrings(vector<Token>& inputVector)
{
    vector<int> strings;
    vector<Token> newVec(inputVector);
    for(int i = 0; i < inputVector.size(); i++)
    {
        if(inputVector[i].getTokenType() == STRING)
        {
            strings.push_back(i);
        }
    }
    for(int i = 0; i < strings.size(); i++)
    {
        for(int j = strings[i]; j < inputVector.size() - 1; j++)
        {
            newVec[j] = newVec[j + 1];
        }
        newVec.pop_back();
    }
    return newVec;
}

vector<int> getIDsFromTokenVector(vector<Token>& inputVector)
{
    vector<int> intVec;
    for(int i = 0; i < inputVector.size(); i++)
    {
        if(inputVector[i].getTokenType() == ID)
        {
            intVec.push_back(i);
        }
    }
    return intVec;
}

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
    tuples = new set<Tuple>((*inputRelation.getTuples()));
    schema = new Schema((*inputRelation.getSchema()));
}

Relation::~Relation()
{
}

Token* Relation::getID() const
{
    return Id;
}

Schema* Relation::getSchema() const
{
    return schema;
}

set<Tuple>* Relation::getTuples() const
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
    vector<Token> noStrings = removeStrings(inputTokens);
    vector<std::pair<Token, vector<int> > > myMap;
    for(int i = 0; i < noStrings.size(); i++)
    {
        bool inserted = false;
        for(int j = 0; j < myMap.size(); j++)
        {
            if(myMap[j].first.getTokensValue() == noStrings[i].getTokensValue())
            {
                myMap[j].second.push_back(i);
                inserted = true;
            }
        }
        if(!inserted && noStrings[i].getTokenType() == ID)
        { 
            vector<int> newVec;
            newVec.push_back(i);
            myMap.push_back(pair<Token, vector<int> >(noStrings[i], newVec) );
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

void Relation::setSchemaFromTuples()
{
    vector<Token> newSchemaTokens;
    set<Tuple>::iterator it = tuples->begin();
    for(int i = 0; i < it->getPairVectorSize(); i++)
    {
        newSchemaTokens.push_back((*it)[i]);
    }
    Schema* deleteSchema = schema;
    schema = new Schema(newSchemaTokens);
    delete deleteSchema;
}

void Relation::setTuples(set<Tuple>* inputTuples)
{
    tuples = inputTuples;
    return;
}

Relation Relation::select(vector<Token>& inputTokens)
{
    Relation newRelation = (*this);
    set<Tuple>* newTuples = new set<Tuple>();
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
                //CHECKS FOR TUPLES WITH CORRECT STRING COMBINATIONS
                if(inputTokens[i].getTokenType() == STRING && j == i) //if this parameter is the placeholder string 
                {
                    if(inputTokens[i].getTokensValue() != thisTuple.getTokenFromPairAt(j).getTokensValue()) //if the values don't match
                    {
                        isTrue = false; //do not add to the new relation
                    }
                }
                //CHECK FOR TUPLES WITH DUPLICATE VALUES FOR DUPLICATE IDs IN QUERY
                else if(inputTokens[i].getTokenType() == ID)
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
            newTuples->insert(thisTuple);
        }
    }
    set<Tuple>* deleteSet = newRelation.getTuples();
    newRelation.setTuples(newTuples);
    delete deleteSet;
    return newRelation;
}

Relation Relation::rename(pair<vector<Token>, vector<Token> >& ruleParameters, Relation& targetRelation)
{
    Relation newRelation = (*this);
    const int FIRST = 0;
    const int SECOND = 1;
    vector<pair<Token, vector<vector<int> > > > myMap;
    for(int i = 0; i < ruleParameters.first.size(); i++) // Make a mapping of the rule parameters to find matches
    {
        vector<vector<int> > intVec;
        vector<int> firstVec;
        vector<int> secondVec;
        intVec.push_back(firstVec);
        intVec.push_back(secondVec);
        bool insert = true;
        for(int k = 0; k < myMap.size(); k++)
        {
            if(ruleParameters.first[i].getTokensValue() == myMap[k].first.getTokensValue()) // If token from first tvector is in map
            {
                Schema* tSchema = targetRelation.getSchema();
                Token thisToken = (*tSchema)[myMap[k].second[FIRST][FIRST]];
                tSchema->renameTokenAt(i, thisToken); // Rename left-side arguments that will be joined
                myMap[k].second[FIRST].push_back(i);
                insert = false; // don't insert that token
            }
        }
        if(insert)
        {
            intVec[FIRST].push_back(i);
            myMap.push_back(pair<Token, vector<vector<int> > >(ruleParameters.first[i], intVec));
        }
    }

    for(int i = 0; i < myMap.size(); i++) // if there are duplicates in the second vector, add to int vector
    {
        for(int j = 0; j < ruleParameters.second.size(); j++)
        {
            if(myMap[i].first.getTokensValue() == ruleParameters.second[j].getTokensValue())
            {
                myMap[i].second[SECOND].push_back(j);
            }
        }
    }

    Schema newSchema(*schema);
    for(int i = 0; i < myMap.size(); i++) // Rename the Schema
    {
        for(int j = 0; j < myMap[i].second[SECOND].size(); j++)
        {
            Schema* tSchema = targetRelation.getSchema();
            Token thisToken = (*tSchema)[myMap[i].second[FIRST][FIRST]];
            newSchema.renameTokenAt(myMap[i].second[SECOND][j], thisToken);
        }
    }
    newRelation.setSchema(newSchema);
    set<Tuple>* newTuples = new set<Tuple>();

    for(set<Tuple>::iterator it = tuples->begin(); it != tuples->end(); it++) // Copy tuples with the renamed Schema
    {
        Tuple thisTuple = (*it);
        Tuple newTuple(thisTuple, newSchema);
        newTuples->insert(newTuple);
    }
    set<Tuple>* deleteTuples = newRelation.getTuples();
    newRelation.setTuples(newTuples);
    delete deleteTuples;

    return newRelation;
}

Relation Relation::project(vector<Token>& inputTokens, vector<Token>* opTokens)
{
    Relation newRelation = (*this);
    bool SchemaFull = true;
    vector<Token> newVec;
    set<Tuple>* newTuples = new set<Tuple>();

    for(set<Tuple>::iterator it = tuples->begin(); it != tuples->end(); it++) // for all the old tuples
    {
        if(opTokens)
        {
            for(int i = 0; i < inputTokens.size(); i++)
            {
                bool insert = false;
                for(int j = 0; j < opTokens->size(); j++)
                {
                    if(inputTokens[i].getTokensValue() == (*opTokens)[j].getTokensValue())
                    {
                        insert = true;
                    }
                }
                if(insert)
                {
                    newVec.push_back((*(schema->getSchematics()))[i]);
                }
            }
        }
        else
        {
            vector<int> intVec = getIDsFromTokenVector(inputTokens);
            for(int i = 0; i < intVec.size(); i++)
            {
                newVec.push_back((*(schema->getSchematics()))[intVec[i]]);
            }
        }
        Tuple newTuple = (*it); // copy this tuple
        newTuple.removePairWithout(newVec); // remove pairs that don't fit projection parameters
        newTuples->insert(newTuple);
    }
    set<Tuple>* deleteTuples = newRelation.getTuples();
    newRelation.setTuples(newTuples);
    delete deleteTuples;
    return newRelation;
}

Relation Relation::Join(pair<vector<Token>, vector<Token> >& pair, Relation* nextRelation)
{
    Relation thisAfterSelect = this->select(pair.first);
    Relation thisAfterProject = thisAfterSelect.project(pair.first, 0);

    if(nextRelation != 0)
    {
        Relation thatAfterSelect = nextRelation->select(pair.second);
        Relation thatAfterRename = thatAfterSelect.rename(pair, *this);
        Relation thatAfterProject = thatAfterRename.project(pair.second, 0);
        Relation allAfterCCP = thisAfterProject.CartesianCrossProduct(pair, thatAfterProject);
        return allAfterCCP;
    }
    else
    {
        return thisAfterProject;
    }
}

Relation Relation::CartesianCrossProduct(pair<vector<Token>, vector<Token> >& pair, Relation& inputRelation)
{
    Relation R1 = (*this);
    set<Tuple>* R1Tuples = new set<Tuple>();
    set<Tuple>* R1delete = R1.getTuples();

    for(set<Tuple>::iterator it = tuples->begin(); it != tuples->end(); it++) // Take cross product of tuples in both relations (out R1)
    {
        Tuple itTuple = (*it);
        for(set<Tuple>::iterator jt = inputRelation.getTuples()->begin(); jt != inputRelation.getTuples()->end(); jt++)
        {
            Tuple jtTuple = (*jt);
            Tuple newTuple = itTuple.combineTuples(jtTuple);
            R1Tuples->insert(newTuple);
        }
    }
    
    R1.setTuples(R1Tuples);
    R1.setSchemaFromTuples();

    vector<Token> schemaTokens = R1.getSchema()->getTVecFromSchema();
    Relation R2 = R1.select(schemaTokens); // Select on R1 to get tuples where duplicates in schema must match

    Relation R3 = R2; // Make a new Relation and then remove the duplicate columns from each tuple
    set<Tuple>* R3Tuples = new set<Tuple>();
    set<Tuple>* R3delete = R3.getTuples();
    for(set<Tuple>::iterator it = R2.getTuples()->begin(); it != R2.getTuples()->end(); it++)
    {
        Tuple thisTuple = (*it);
        Tuple newTuple = thisTuple.removeDuplicates();
        R3Tuples->insert(newTuple);
    }
    R3.setTuples(R3Tuples);
    R3.setSchemaFromTuples();

    pair.first = combineTokenVectors(pair.first, pair.second); // Update first of Token vectors
    delete R1delete;
    delete R3delete;

    return R3;
}

Relation Relation::Union(pair<vector<Token>, vector<Token> >& pair, Relation& rightRelation)
{
    Relation newRelation = (*this);
    Relation copyRelation = rightRelation;
    Relation rightAfterRename = copyRelation.rename(pair, newRelation);
    vector<Token>* vecPoint = new vector<Token>(pair.first);
    Relation rightAfterProject = rightAfterRename.project(pair.second, vecPoint);
    set<Tuple>* rightTuples = rightAfterProject.getTuples();
    for(set<Tuple>::iterator it = rightTuples->begin(); it != rightTuples->end(); it++)
    {
        Tuple thisTuple = (*it);
        newRelation.insertTuple(thisTuple);
    }
    return newRelation;
}
