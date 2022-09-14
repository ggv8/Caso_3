# pragma once
# include <regex>
# include <iostream>
# include <string>
# include "../structs/Stack.hpp"

using namespace std;

enum Case
{
    NUMBER     = 0,
    ADDITION   = 1,
    PRODUCT    = 2,
    OPEN       = 3,
    CLOSE      = 4,
    WHITESPACE = 5
};

string re_cases[6] = {"^\\d+", "^(?:\\+|-)", "^(?:\\*|/|%)", "^\\(", "^\\)", "^\\s"};

class PostfixParser
{
    private:
        string notation;
        Stack<string>* callStack;
        Stack<double>* valueStack;

        bool hasPriority(Case pCase) {
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

        void buildCase(Case pMatchCase, string* pMatch) {
            switch (pMatchCase) {
                case NUMBER:
                    notation.append( *pMatch + " " );
                    break;

                case ADDITION:
                case PRODUCT:
                    if (hasPriority(pMatchCase)) {
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

        void solveCase(Case pMatchCase, string* pMatch) {
            double lhsNumber, rhsNumber;
            switch (pMatchCase) {
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

        void appendCalls() {
            string topCall;
            while (! callStack->isEmpty()) {
                topCall = *callStack->pop();
                if (topCall != "(") {
                    notation.append( topCall + " ");
                }
            }
        }

        void findClosing() {
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

    public:
        PostfixParser() {
            notation = "";
            callStack = new Stack<string>;
            valueStack = new Stack<double>;
        }

        const string& getNotation() {
            return notation;
        }

        void parseInfix(string& pInfix) {
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
            notation.pop_back();
        }

        double evaluate() {
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
};