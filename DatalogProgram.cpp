#include "DatalogProgram.h"

DatalogProgram::DatalogProgram()
{
    slist = 0;
}

DatalogProgram::~DatalogProgram()
{
    delete slist;
    delete flist;
    delete dman;
    delete rlist;
    delete qlist;
}

void DatalogProgram::setSchemesList(SchemesList* schemeslist)
{
    slist = schemeslist;
    return;
}

SchemesList* DatalogProgram::getSchemesList()
{
    return slist;
}

void DatalogProgram::setFactsList(FactsList* factslist)
{
    flist = factslist;
    return;
}

FactsList* DatalogProgram::getFactsList()
{
    return flist;
}

void DatalogProgram::setRulesList(RulesList* ruleslist)
{
    rlist = ruleslist;
    return;
}

RulesList* DatalogProgram::getRulesList()
{
    return rlist;
}

void DatalogProgram::setQueryList(QueryList* querylist)
{
    qlist = querylist;
    return;
}

QueryList* DatalogProgram::getQueryList()
{
    return qlist;
}

void DatalogProgram::setDomain(Domain* domain)
{
    dman = domain;
}

Domain* DatalogProgram::getDomain()
{
    return dman;
}

std::string DatalogProgram::toString()
{
    string out;
    stringstream stoi; stoi << (slist->getSize() + 1);
    stringstream ftoi; ftoi << flist->getSize();
    stringstream rtoi; rtoi << rlist->getSize();
    stringstream qtoi; qtoi << (qlist->getSize() + 1);
    stringstream dtoi; dtoi << dman->getSize();
    out += "Schemes(" + stoi.str();
    out += "):";
    out += slist->toString();
    out += "\nFacts(" + ftoi.str();
    out += "):";
    out += flist->toString();
    out += "\nRules(" + rtoi.str();
    out += "):";
    out += rlist->toString();
    out += "\nQueries(" + qtoi.str();
    out += "):";
    out += qlist->toString();
    out += "\nDomain(" + dtoi.str();
    out += "):";
    out += dman->toString();
    out += "\n";
    return out;
}
