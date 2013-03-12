#ifndef SCHEMES_LIST_H_
#define SCHEMES_LIST_H_

#include "Scheme.h"

class SchemesList
{
  public:
    SchemesList();
    ~SchemesList();

    void setScheme(Scheme* inputScheme);

    void addScheme(Scheme* scheme);

    int getSize();

    std::string toString();

    vector<Scheme*>* getSchemes();

  private:

    Scheme* scheme;
    vector<Scheme*> schemes;
    int listSize;

};

#endif
