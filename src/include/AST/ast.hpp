#ifndef __AST_H
#define __AST_H

#include <cstdint>
#include <string>
#include <vector>
using namespace std;

struct Location {
    Location(const uint32_t line, const uint32_t col) : line(line), col(col) {}

    uint32_t line;
    uint32_t col;
};

typedef vector< class AstNode* > Nodevec;
typedef class AstNode* Node;

enum enumoperator{
    OP_ASSIGN,
    OP_OR,
    OP_AND,
    OP_NOT,
    OP_LESS,
    OP_LESS_OR_EQUAL,
    OP_EQUAL,
    OP_GREATER,
    OP_GREATER_OR_EQUAL,
    OP_NOT_EQUAL,
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_MOD,
    UNKNOWN_OP
};

enum enumTypeSet{ //which type to use (e.x. array needs[], constant need to print constant)
    SET_SCALAR,
    SET_ARR,
    SET_CONST_LIT,
    UNKNOWN_SET
};

enum enumType{ //the info of respectively type
    TYPE_INT,
    TYPE_REAL,
    TYPE_STRING,
    TYPE_BOOLEAN,
    TYPE_VOID,
    UNKNOWN_TYPE
};

enum BooleanLiteral{
    Boolean_TRUE,
    Boolean_FALSE
};

typedef struct __VariableInfo{
    enumTypeSet type_set;
    enumType type;
    vector<int> array_val;
    int int_lit;
    double real_lit;
    std::string string_lit;
    BooleanLiteral boolean_lit;
} VariableInfo ;

struct NodeWithTypeList{
    Node node;
    VariableInfo* type;
    uint counter;
};


class AstNode {
  public:
    AstNode(const uint32_t line, const uint32_t col);
    virtual ~AstNode() = 0;

    const Location getLocation() const;
    virtual void print() = 0;
    
  public:
    int spacecounter;

  protected:
    const Location location;
};

#endif
