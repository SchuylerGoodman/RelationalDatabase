#include "Lex.h"

#include "Input.h"
#include "TokenType.h"
#include "Utils.h"
#include <iostream>

using namespace std;

Lex::Lex() {
	input = new Input();
    generateTokens(input);
}

Lex::Lex(const char* filename) {
    input = new Input(filename);
    generateTokens(input);
}

Lex::Lex(istream& istream) {
    input = new Input(istream);
    generateTokens(input);
}

Lex::Lex(const Lex& lex) {
    input = new Input(*lex.input);
    tokens = new vector<Token*>();

    vector<Token*>::iterator iter;
    for(iter=lex.tokens->begin(); iter != lex.tokens->end(); iter++) {
        Token* newToken = new Token(**iter);
        tokens->push_back(newToken);
    }

    index = lex.index;
    state = lex.state;
}

Lex::~Lex(){
    for (int i = 0; i < tokens->size(); i++) {
        delete (*tokens)[i];
    }
    delete tokens;
    delete input;
}

bool Lex::operator==(const Lex& lex) {
    bool result = (tokens->size() == lex.tokens->size()) && (index == lex.index);
    if(result) {
        vector<Token*>::iterator iter1;
        vector<Token*>::iterator iter2;
        iter1 = tokens->begin();
        iter2 = lex.tokens->begin();
        while(result && iter1 != tokens->end() && iter2 != lex.tokens->end()) {
            result = **iter1 == **iter2;
            iter1++;
            iter2++;
        }
        result = result && iter1 == tokens->end() && iter2 == lex.tokens->end();
    }
    return result;
}

string Lex::toString() const {
    int count = 0;
    string result;
    while(count < tokens->size()) {
        Token* token = (*tokens)[count];
        result += token->toString();
        count++;
    }
    result += "Total Tokens = ";
    string countToString;
    result += itoa(countToString, count);
    result += "\n";
    return result;
}

void Lex::generateTokens(Input* input) {
    tokens = new vector<Token*>();
    index = 0;

    state = Start;
    while(state != End) {
        state = nextState();
    }
    emit(EOF);
}

Token* Lex::getCurrentToken() {
    return (*tokens)[index];
}

void Lex::advance() {
    index++;
}

bool Lex::hasNext() {
    return index < tokens->size();
}

State Lex::nextState() {
    State result;
    char character;
    switch(state) {
        case Start:               result = getNextState(); break;
        case Comma:               emit(COMMA); result = getNextState(); break;
        case Multiply:            emit(MULTIPLY); result = getNextState(); break;
        case Add:                 emit(ADD); result = getNextState(); break;
        case Q_Mark:              emit(Q_MARK); result = getNextState(); break;
        case LeftParen:           emit(LEFT_PAREN); result = getNextState(); break;
        case RightParen:          emit(RIGHT_PAREN); result = getNextState(); break;
        case Period:              emit(PERIOD); result = getNextState(); break;
        case SawColon:
            character = input->getCurrentCharacter();
            if(character == '-') {
                result = Colon_Dash;
                input->advance();
            } else { //Every other character
                emit(COLON);
                result = getNextState();
            }
            break;
        case Colon_Dash:          emit(COLON_DASH); result = getNextState(); break;
        case BeginningOfComment:
            character = input->getCurrentCharacter();
            if (character == '|') {
                result = MultilineComment;
                input->advance();
            } else if(character == '\n') {
                emit(COMMENT);
                input->advance();
                input->mark();
                result = getNextState();
            } else {
                result = Comment;
                input->advance();
            }
            break;
        case Comment:
            character = input->getCurrentCharacter();
            if (character == '\n') {
                emit(COMMENT);
                input->advance();
                input->mark();
                result = getNextState();
            } else {
                result = Comment;
                input->advance();
            }
            break;
        case MultilineComment:
            character = input->getCurrentCharacter();
            if (character == '|') {
                result = PossibleEndOfComment;
            } else if(character == -1) {
                result = Undefined;
            } else {
                result = MultilineComment;
            }
            input->advance();
            break;
        case PossibleEndOfComment:
            character = input->getCurrentCharacter();
            if (character == '|') {
                result = PossibleEndOfComment;
                input->advance();
            } else if(character == -1) {
                result = Undefined;
            } else if(character == '#') {
                input->advance();
                emit(COMMENT);
                result = getNextState();
            } else {
                result = MultilineComment;
            }
            break;
        case SawAQuote:  
            character = input->getCurrentCharacter();
            if(character == '\'') {
                result = PossibleEndOfString;
            } else if(character == -1) {
                result = Undefined;
            } else { //Every other character
                result = ProcessingString;
            }
            input->advance();
            break;
        case ProcessingString:  
            character = input->getCurrentCharacter();
            if(character == '\'') {
                result = PossibleEndOfString;
            } else if(character == -1) {
                result = Undefined;
            } else { //Every other character
                result = ProcessingString;
            }
            input->advance();
            break;
        case PossibleEndOfString:
            if(input->getCurrentCharacter() == '\'') {
                input->advance();
                result = ProcessingString;
            } else { //Every other character
                emit(STRING);
                result = getNextState();
            }
            break;
        case Schemes:
            emit(SCHEMES);
            result = getNextState();
            break;
        case Facts:
            emit(FACTS);
            result = getNextState();
            break;
        case Queries:
            emit(QUERIES);
            result = getNextState();
            break;
        case Rules:
            emit(RULES);
            result = getNextState();
            break;
        case Identifier:
            character = input->getCurrentCharacter();
            while(isalnum(character)) {
                input->advance();
                character = input->getCurrentCharacter();
            }
            emit(ID);
            result = getNextState();
            break;
        case Whitespace:
            input->mark();
            result = getNextState();
            break;
        case End:
            throw "ERROR:: in End state:, the Input should be empty once you reach the End state."; 
            break;
        case Undefined:
            emit(UNDEFINED);
            result = getNextState();
            break;
    };
    return result;
}

State Lex::getNextState() {
    State result;
    char currentCharacter = input->getCurrentCharacter();
    bool isID = false;
    //The handling of checking for whitespace and setting the result to Whilespace and
    //checking for letters and setting the result to Id will probably best be handled by
    //if statements rather then the switch statement.
    switch(currentCharacter) {
        case ','  : result = Comma; break;
        case '.'  : result = Period; break;
        case '*'  : result = Multiply; break;
        case '+'  : result = Add; break;
        case '?'  : result = Q_Mark; break;
        case '('  : result = LeftParen; break;
        case ')'  : result = RightParen; break;
        case ':'  : result = SawColon; break;
        case '#'  : result = BeginningOfComment; break;
        case '\'' : result = ProcessingString; break;
        case -1   : result = End; break;
        default: 
            if(isspace(currentCharacter)) {
                result = Whitespace; break;
            } else if(isalpha(currentCharacter)) {
                isID = true;
                result = processID();
            } else {
                result = Undefined;
            }
    }
    if(isID == false) {
        input->advance();
    }
    return result;
}

State Lex::processID() {
    char character = input->getCurrentCharacter();
    State result;
    if (character == 'S') {
        input->advance();
        character = input->getCurrentCharacter();
        if(character == 'c') {
            input->advance();
            character = input->getCurrentCharacter();
            if(character == 'h') {
                input->advance();
                character = input->getCurrentCharacter();
                if(character == 'e') {
                    input->advance();
                    character = input->getCurrentCharacter();
                    if(character == 'm') {
                          input->advance();
                          character = input->getCurrentCharacter();
                        if(character == 'e') {
                              input->advance();
                              character = input->getCurrentCharacter();
                            if(character == 's') {
                                  input->advance();
                                  character = input->getCurrentCharacter();
                                if(isalnum(character)) {
                                    result = Identifier;
                                } else {
                                    result = Schemes;
                                }
                            } else {
                                result = Identifier;
                            }
                        } else {
                            result = Identifier;
                        }
                    } else {
                        result = Identifier;
                    }
                } else {
                    result = Identifier;
                }
            } else {
                result = Identifier;
            }
        } else {
            result = Identifier;
        }
    } else if (character == 'F') {
        input->advance();
        character = input->getCurrentCharacter();
        if(character == 'a') {
            input->advance();
            character = input->getCurrentCharacter();
            if(character == 'c') {
                  input->advance();
                  character = input->getCurrentCharacter();
                if(character == 't') {
                    input->advance();
                    character = input->getCurrentCharacter();
                    if(character == 's') {
                        input->advance();
                        character = input->getCurrentCharacter();
                        if(isalnum(character)) {
                            result = Identifier;
                        } else {
                            result = Facts;
                        }
                    } else {
                        result = Identifier;
                    }
                } else {
                    result = Identifier;
                }
            } else {
                result = Identifier;
            }
        } else {
            result = Identifier;
        }
    } else if (character == 'Q') {
        input->advance();
        character = input->getCurrentCharacter();
        if(character == 'u') {
            input->advance();
            character = input->getCurrentCharacter();
            if(character == 'e') {
                input->advance();
                character = input->getCurrentCharacter();
                if(character == 'r') {
                    input->advance();
                    character = input->getCurrentCharacter();
                    if(character == 'i') {
                        input->advance();
                        character = input->getCurrentCharacter();
                        if(character == 'e') {
                            input->advance();
                            character = input->getCurrentCharacter();
                            if(character == 's') {
                                input->advance();
                                character = input->getCurrentCharacter();
                                if(isalnum(character)) {
                                    result = Identifier;
                                } else {
                                    result = Queries;
                                }
                            } else {
                                result = Identifier;
                            }
                        } else {
                            result = Identifier;
                        }
                    } else {
                        result = Identifier;
                    }
                } else {
                    result = Identifier;
                }
            } else {
                result = Identifier;
            }
        } else {
            result = Identifier;
        }
    } else if(character == 'R') {
      input->advance();
      character = input->getCurrentCharacter();
        if(character == 'u') {
            input->advance();
            character = input->getCurrentCharacter();
            if(character == 'l') {
                input->advance();
                character = input->getCurrentCharacter();
                if(character == 'e') {
                    input->advance();
                    character = input->getCurrentCharacter();
                    if(character == 's') {
                        input->advance();
                        character = input->getCurrentCharacter();
                        if(isalnum(character)) {
                            result = Identifier;
                        } else {
                            result = Rules;
                        }
                    } else {
                        result = Identifier;
                    }
                } else {
                    result = Identifier;
                }
            } else {
                result = Identifier;
            }
        } else {
            result = Identifier;
        }
    } else {
        result = Identifier;
    }
    return result;
}

void Lex::emit(TokenType tokenType) {
    Token* token = new Token(tokenType, input->getTokensValue(), input->getCurrentTokensLineNumber());
    storeToken(token);
    input->mark();
}

void Lex::storeToken(Token* token) {
    //This section shoud ignore whitespace and comments and change the token type to the appropriate value
    //if the value of the token is "Schemes", "Facts", "Rules", or "Queries".
    tokens->push_back(token);
}
