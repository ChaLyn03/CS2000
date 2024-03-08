// CompilerParser.cpp
#include "CompilerParser.h"
#include <stdexcept>


/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) : tokens(tokens) {
    currentToken = this->tokens.begin(); // Initialize the iterator to the start of the list
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    // The program must start with a class
    ParseTree* program = new ParseTree("program", "");
    program->addChild(compileClass());
    return program;
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    // Must start with 'class' keyword
    mustBe("keyword", "class");
    ParseTree* classNode = new ParseTree("class", "");

    // Next token must be an identifier (class name)
    classNode->addChild(mustBe("identifier", ""));

    // Next token must be '{'
    mustBe("symbol", "{");

    // ... Here you would parse class variable declarations and subroutines ...

    // Next token must be '}'
    mustBe("symbol", "}");

    return classNode;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    // Example based on a typical variable declaration syntax:
    // 'static' type varName ('=' expression)? (',' varName ('=' expression)?)* ';'
    
    ParseTree* varDecNode = new ParseTree("classVarDec", "");

    // 'static' or 'field'
    varDecNode->addChild(mustBe("keyword", ""));
    // type
    varDecNode->addChild(mustBe("identifier", ""));
    // varName
    varDecNode->addChild(mustBe("identifier", ""));

    // Possible initialization and additional variables
    // ...

    // ';'
    mustBe("symbol", ";");

    return varDecNode;
}

/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    // Example based on a typical subroutine declaration syntax:
    // ('constructor' | 'function' | 'method') ('void' | type) subroutineName '(' parameterList ')' subroutineBody
    
    ParseTree* subroutineNode = new ParseTree("subroutineDec", "");

    // 'constructor', 'function', or 'method'
    subroutineNode->addChild(mustBe("keyword", ""));
    // 'void' or type
    subroutineNode->addChild(mustBe("identifier", ""));
    // subroutineName
    subroutineNode->addChild(mustBe("identifier", ""));
    // '('
    mustBe("symbol", "(");
    // parameterList
    subroutineNode->addChild(compileParameterList());
    // ')'
    mustBe("symbol", ")");
    // subroutineBody
    subroutineNode->addChild(compileSubroutineBody());

    return subroutineNode;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* parameterList = new ParseTree("parameterList", "");
    
    // Check if there are parameters by looking for a type
    while (have("keyword", "int") || have("keyword", "char") || 
           have("keyword", "boolean") || have("identifier", "")) {
        // Add type
        parameterList->addChild(mustBe("keyword", ""));
        // Add varName
        parameterList->addChild(mustBe("identifier", ""));
        // Check for more parameters
        if (have("symbol", ",")) {
            parameterList->addChild(mustBe("symbol", ","));
        } else {
            break; // No more parameters
        }
    }
    
    return parameterList;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    ParseTree* subroutineBody = new ParseTree("subroutineBody", "");

    // Start with '{'
    subroutineBody->addChild(mustBe("symbol", "{"));
    
    // Compile variable declarations
    while (have("keyword", "var")) {
        subroutineBody->addChild(compileVarDec());
    }
    
    // Compile statements
    subroutineBody->addChild(compileStatements());

    // End with '}'
    subroutineBody->addChild(mustBe("symbol", "}"));
    
    return subroutineBody;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    return NULL;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
Token* CompilerParser::current() {
    // Check that we're not at the end of the list before dereferencing the iterator
    if (currentToken != tokens.end()) {
        return *currentToken;
    } else {
        // If we're at the end, we can't return a valid token, so throw an exception
        throw std::runtime_error("Attempted to access a token past the end of the list.");
    }
}

void CompilerParser::next() {
    if (currentToken != tokens.end()) {
        ++currentToken; // Safely advance the iterator
    }
    // No else block needed here because we don't want to advance past the end
}

bool CompilerParser::have(const std::string& expectedType, const std::string& expectedValue) {
    Token* token = current(); // current() now has a safety check, so it's okay to call here
    if (token != nullptr && token->getType() == expectedType && 
        (expectedValue.empty() || token->getValue() == expectedValue)) {
        return true;
    }
    return false;
}

Token* CompilerParser::mustBe(const std::string& expectedType, const std::string& expectedValue) {
    if (have(expectedType, expectedValue)) {
        Token* token = current();
        next();
        return token;
    } else {
        // Throw an exception with more information if possible
        std::string error = "Expected token type '" + expectedType + "' with value '" + expectedValue + "' not found.";
        throw ParseException(error.c_str());
    }
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */

const char* ParseException::what() const noexcept {
    return message.c_str();
}



