#include "State.h"

using namespace std;

string StateToString(State tokenType){
    string result = "";
    switch(tokenType){
        case Comma:                      result = "Comma"; break;
        case Period:                     result = "Period"; break;
        case Multiply:                   result = "Multiply"; break;
        case Add:                        result = "Add"; break;
        case Q_Mark:                     result = "Q_Mark"; break;
        case Whitespace:                 result = "Whitespace"; break;
        case LeftParen:                  result = "LeftParen"; break;
        case RightParen:                 result = "RightParen"; break;
        case SawColon:                   result = "SawColon"; break;
        case Colon_Dash:                 result = "Colon_Dash"; break;
        case BeginningOfComment:         result = "BeginningOfComment"; break;
        case MultilineComment:           result = "MultilineComment"; break;
        case Comment:                    result = "Comment"; break;
        case PossibleEndOfComment:       result = "PossibleEndOfComment"; break;
        case Identifier:                 result = "Identifier"; break;
        case Schemes:                    result = "Schemes"; break;
        case Facts:                      result = "Facts"; break;
        case Rules:                      result = "Rules"; break;
        case Queries:                    result = "Queries"; break;
        case SawAQuote:                  result = "SawAQuote"; break;
        case ProcessingString:           result = "ProcessingString"; break;
        case PossibleEndOfString:        result = "PossibleEndOfString"; break;
        case Start:                      result = "Start"; break;
        case End:                        result = "End"; break;
        case Undefined:                  result = "Undefined"; break;
    }
    return result;
};
