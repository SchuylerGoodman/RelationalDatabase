#ifndef DOMAIN_H_
#define DOMAIN_H_

#include "Lex.h"
#include <string>
#include <set>

class Domain
{

  public:
    
    Domain();
    ~Domain();

    /* adds a string to the string vector in this domain object

    Parameters: String to be added
    PreCondition:  None
    PostCondition:  String has either been added to the object, or it already existed in the vector, in which case it was ignored
    */
    void addString(std::string inString);

    /* gets the size of the vector of strings in the object

    Parameters:  None
    PreCondition:  None
    PostCondition:  number of strings in the vector returned as an int
    */
    int getSize();

    /* Formats the strings in the vector for output with each string creating a new line and two spaces before it.

    Parameters:  None
    PreCondition:  None
    PostCondition:  Formatted output for strings in vector returned
    */
    std::string toString();

  private:

    set<std::string> strings;

    int listSize;

};

#endif
