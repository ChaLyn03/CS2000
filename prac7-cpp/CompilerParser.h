// CompilerParser.h
#ifndef COMPILERPARSER_H
#define COMPILERPARSER_H

#include "ParseTree.h"
#include "Token.h"
#include <list>
#include <iterator>

class CompilerParser {
private:
    std::list<Token*> tokens;
    std::list<Token*>::iterator currentToken;

public:
    CompilerParser(std::list<Token*> tokens);

    ParseTree* compileProgram();
    ParseTree* compileClass();
    ParseTree* compileClassVarDec();
    ParseTree* compileSubroutine();
    ParseTree* compileParameterList();
    ParseTree* compileSubroutineBody();
    ParseTree* compileVarDec();

    ParseTree* compileStatements();
    ParseTree* compileLet();
    ParseTree* compileIf();
    ParseTree* compileWhile();
    ParseTree* compileDo();
    ParseTree* compileReturn();

    ParseTree* compileExpression();
    ParseTree* compileTerm();
    ParseTree* compileExpressionList();
    
    Token* current();
    void next();
    bool have(const std::string& expectedType, const std::string& expectedValue);
    Token* mustBe(const std::string& expectedType, const std::string& expectedValue);
};

class ParseException : public std::exception {
private:
    std::string message;
public:
    ParseException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override;
};



#endif /* COMPILERPARSER_H */