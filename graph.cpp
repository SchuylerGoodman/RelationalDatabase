#include "Database.h"

//+++++++++++GRAPH+++++++++++++++++++++++++++++++++++++++++++

graph::graph()
{}

graph::graph(Database* inputDatabase)
{
    for(int i = 0; i < inputDatabase->getRulesListSize(); i++) //For every rule
    {
        Rule* thisRule = inputDatabase->getRuleAt(i);
        Token* thisToken = thisRule->getHeadPredicateID();
        int thisExists = graphMap.count(*thisToken);
        if(thisExists == 0)
        {
            Relation* thisRelation = inputDatabase->findRelation(thisToken);
            graphnode* newThisGnode = new graphnode(thisRelation);
            graphMap[(*thisToken)] = newThisGnode;
        }

        for(int j = 0; j < thisRule->getPredicateList()->getSize() + 1; j++) //For all predicates
        {
            Token* thatToken = thisRule->getParameterIDAt(j);
            int thatExists = graphMap.count(*thatToken);
            if(thisExists == 0)
            {
                Relation* thatRelation = inputDatabase->findRelation(thatToken);
                graphnode* newThatGnode = new graphnode(thatRelation);
                graphMap[(*thatToken)] = newThatGnode;
            }
            if(!graphMap[(*thisToken)]->find(graphMap[(*thatToken)]))
            {
                graphMap[(*thisToken)]->addEdge(graphMap[(*thatToken)]); //add pointer to new node to new H.P. node
            }
        }
    }
}

graph::~graph()
{}

vector<graphnode*>* graph::buildDFS(Query* inputQuery)
{
    this->reset();
    Token* queryToken = inputQuery->getQueryID();
    int hasDependencies = graphMap[(*queryToken)]->getEdgeNumber();
    if(hasDependencies > 0)
    {
        int PO = 1;
        vector<graphnode*>* topTHIS = new vector<graphnode*>();
        graphnode* startNode = graphMap[(*queryToken)];
        PO = startNode->recursiveDFS(PO, topTHIS);
      //  startNode->setPostorder(PO);
        //topTHIS->push_back(startNode);
        cycleDetect(topTHIS);
        return topTHIS;
    }
    return 0;
}

string graph::toString()
{
    string out;
    for(map<Token, graphnode*>::iterator it = graphMap.begin(); it != graphMap.end(); it++)
    {
        out += "\n  " + it->first.getTokensValue() + ": ";
        out += it->second->toString();
    }
    return out;
}

void graph::reset()
{
    for(map<Token, graphnode*>::iterator it = graphMap.begin(); it != graphMap.end(); it++)
    {
        it->second->reset();
    }
    return;
}

void graph::cycleDetect(vector<graphnode*>* tippity)
{
    for(int i = 0; i < tippity->size(); i++) // for every topsorted node
    {
        for(int j = 0; j < (*tippity)[i]->getEdgeNumber(); j++) // for every node it connects to
        {
            graphnode* nextNizzle = (*(*tippity)[i])[j];
            if((*tippity)[i]->getPostorder() <= (*(*tippity)[i])[j]->getPostorder()) // if connecting node has higher postorder number...
            {
                int count = i;
                graphnode* nodeIterator = (*tippity)[count];
                while(nodeIterator != (*(*tippity)[i])[j]) // make sure all topsorted nodes between them go through the LFP algorithm
                {
                    nodeIterator->setLFP_true();
                    ++count;
                    nodeIterator = (*tippity)[count];
                }
                nodeIterator->setLFP_true(); // including itself, or the last one
            }
        }
    }
    return;
}
        

//+++++++++++GRAPHNODE++++++++++++++++++++++++++++++++++++++

graphnode::graphnode()
{}

graphnode::graphnode(Relation* inputRelation)
{
    relation = inputRelation;
    visited = false;
    leastFixedPoint = false;
    postorder = -1;
}

graphnode::~graphnode()
{}

void graphnode::addEdge(graphnode* inGraphnode)
{
    connections.push_back(inGraphnode);
    return;
}

void graphnode::setPostorder(int& po)
{
    postorder = po;
    return;
}

int graphnode::getPostorder()
{
    return postorder;
}

graphnode* graphnode::operator[](const int& index) const
{
    return connections[index];
}

int graphnode::getEdgeNumber()
{
    return connections.size();
}

Relation* graphnode::getRelation()
{
    return relation;
}

string graphnode::toString()
{
    string out;
    for(int i = 0; i < connections.size(); i++)
    {
        out += connections[i]->getRelation()->getID()->getTokensValue();
        if(i + 1 < connections.size())
        {
            out += ", ";
        }
    }
    return out;
}

string graphnode::simpleToString()
{
    string out;
    out += relation->getID()->getTokensValue();
    stringstream ss;
    ss << " <" << postorder << ", " << leastFixedPoint << ">";
    out += ss.str();
    return out;
}

bool graphnode::find(graphnode* searchForTHIS)
{
    for(int i = 0; i < connections.size(); i++)
    {
        if(connections[i] == searchForTHIS)
        {
            return true;
        }
    }
    return false;
}

int graphnode::recursiveDFS(int po, vector<graphnode*>* topsyTurvy)
{
    visited = true;
    for(int i = 0; i < connections.size(); i++)
    {
        if(!connections[i]->seen())
        {
            po = connections[i]->recursiveDFS(po, topsyTurvy);
        }
    }
    postorder = po;
    topsyTurvy->push_back(this);
    return po + 1;
}

bool graphnode::seen()
{
    return visited;
}

void graphnode::reset()
{
    visited = false;
    leastFixedPoint = false;
    postorder = -1;
}

bool graphnode::lfp()
{
    return leastFixedPoint;
}

void graphnode::setLFP_true()
{
    leastFixedPoint = true;
}
