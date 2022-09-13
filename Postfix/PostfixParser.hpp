# pragma once
# include <string>
# include "../structs/Stack.hpp"

enum Case
{
    NUMBER     = 0,
    ADDITION   = 1,
    PRODUCT    = 2,
    OPEN       = 3,
    CLOSE      = 4,
    WHITESPACE = 5
};

class PostfixParser
{
    public:
        PostfixParser();
        const std::string& getNotation();
        void parseInfix(std::string& pInfix);
        double evaluate();

    private:
        std::string notation;
        Stack<std::string>* callStack;
        Stack<double>* valueStack;

        bool hasPriority(Case pCase);
        void buildCase(Case pCase, std::string* pMatch);
        void solveCase(Case pCase, std::string* pMatch);
        void appendCalls();
        void findClosing();

};