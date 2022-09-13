# include <regex>
# include <iostream>
# include "PostfixParser.hpp"

using namespace std;

string re_cases[6] = {"^\\d+", "^(?:\\+|-)", "^(?:\\*|/|%)", "^\\(", "^\\)", "^\\s"};

// Public methods
PostfixParser::PostfixParser() {
    notation = "";
    callStack = new Stack<string>;
    valueStack = new Stack<double>;
}

const string& PostfixParser::getNotation() {
    return notation;
}

void PostfixParser::parseInfix(string& pInfix) {
    notation = "";
    smatch results;
    regex expression;

    while (! pInfix.empty()) {
        int search = Case::NUMBER;
        for (; search <= Case::WHITESPACE; search++) {
            expression.assign(re_cases[search]);
            if (regex_search(pInfix, results, expression)) {
                string* ptrMatch = new string(results.str());
                buildCase( Case(search), ptrMatch );
                pInfix = results.suffix().str();
            }
        }
        
    }
    appendCalls();
}

double PostfixParser::evaluate() {
    string postfix = notation;
    smatch results;
    regex expression;

    while (! postfix.empty()) {
        int search = Case::NUMBER;
        for (; search <= Case::WHITESPACE; search++) {
            expression.assign(re_cases[search]);
            if (regex_search(postfix, results, expression)) {
                string* ptrMatch = new string(results.str());
                solveCase( Case(search), ptrMatch );
                postfix = results.suffix().str();
            }
        }
    }
    return *valueStack->pop();
}

// Private methods
bool PostfixParser::hasPriority(Case pCase) {
    bool result = callStack->isEmpty();
    switch (pCase) {
        case ADDITION:
            if (! result) {
                string topCall = *callStack->top();
                result = (topCall == "(");
            }
            break;
        
        case PRODUCT:
            if (! result) {
                string topCall = *callStack->top();
                result = (topCall == "(" || topCall == "+" || topCall == "-");
            }
            break;
    }
    return result;
}

void PostfixParser::buildCase(Case matchCase, string* pMatch) {
    switch (matchCase) {
        case NUMBER:
            notation.append( *pMatch + " " );
            break;

        case ADDITION:
        case PRODUCT:
            if (hasPriority(matchCase)) {
                callStack->push(pMatch);
            } else {
                appendCalls();
                callStack->push(pMatch);
            }
            break;

        case OPEN:
            callStack->push(pMatch);
            break;

        case CLOSE:
            findClosing();
            break;

        default:
            break;
    }
}

void PostfixParser::solveCase(Case pCase, string* pMatch) {
    double lhsNumber, rhsNumber;
    switch (pCase) {
        case NUMBER:
            rhsNumber = std::stod(*pMatch);
            valueStack->push(new double(rhsNumber));
            break;

        case ADDITION:
        case PRODUCT:
            rhsNumber = *valueStack->pop();
            lhsNumber = *valueStack->pop();
            if (*pMatch == "+") {
                lhsNumber += rhsNumber;
            } else if (*pMatch == "-") {
                lhsNumber -= rhsNumber;
            } else if (*pMatch == "*") {
                lhsNumber *= rhsNumber;
            } else if (*pMatch == "/") {
                lhsNumber /= rhsNumber;
            } else if (*pMatch == "%") {
                lhsNumber = int(lhsNumber) % int(rhsNumber);
            }
            valueStack->push(new double(lhsNumber));
            break;
        
        default:
            break;
    }
}

void PostfixParser::appendCalls() {
    string topCall;
    while (! callStack->isEmpty()) {
        topCall = *callStack->pop();
        if (topCall != "(") {
            notation.append( topCall + " ");
        }
    }
}

void PostfixParser::findClosing() {
    string topCall;
    while (! callStack->isEmpty()) {
        topCall = *callStack->pop();
        if (topCall != "(") {
            notation.append(topCall + " ");
        } else {
            break;
        }
    }
}