#include "Relation.h"

Relation::Relation()
{
    tuples = 0;
    schema = 0;
    Id = 0;
}

Relation::Relation(Scheme* inputScheme)
{

    tuples = new set<Tuple*>();

    Id = inputScheme->getSchemeID(); //set main ID to Scheme ID

    schema = setSchema(inputScheme->getIDList()); //set Schema to Scheme ID List

}

Relation::~Relation()
{
}

Token* Relation::getID()
{
    return Id;
}

Schema* Relation::getSchema()
{
    return schema;
}

set<Tuple*>* Relation::getTuples()
{
    return tuples;
}

int Relation::getSchemaCount()
{
    return schema->getListSize();
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

void Relation::insertTuple(ConstantList* inputConstantList)
{
    tuples->insert(new Tuple(schema, inputConstantList));
}

string Relation::toString()
{
    string out = "";
    out += Id->getTokensValue();
    out += ":";
    out += schema->toString() + "\n";
    for(set<Tuple*>::iterator it = tuples->begin(); it != tuples->end(); it++)
    {
        for(int i = 0; i < Id->getTokensValue().length(); i++)
        {
            out += " ";
        }
        out += "  " + (*it)->toString() + "\n";
    }
    return out;
}
