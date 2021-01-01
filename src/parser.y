%{
#include "AST/ast.hpp"
#include "AST/program.hpp"
#include "AST/decl.hpp"
#include "AST/variable.hpp"
#include "AST/ConstantValue.hpp"
#include "AST/function.hpp"
#include "AST/CompoundStatement.hpp"
#include "AST/print.hpp"
#include "AST/expression.hpp"
#include "AST/BinaryOperator.hpp"
#include "AST/UnaryOperator.hpp"
#include "AST/FunctionInvocation.hpp"
#include "AST/VariableReference.hpp"
#include "AST/assignment.hpp"
#include "AST/read.hpp"
#include "AST/if.hpp"
#include "AST/while.hpp"
#include "AST/for.hpp"
#include "AST/return.hpp"

#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;

#define YYLTYPE yyltype

typedef struct YYLTYPE {
    uint32_t first_line;
    uint32_t first_column;
    uint32_t last_line;
    uint32_t last_column;
} yyltype;

/* Declared by scanner.l */
extern uint32_t line_num;
extern char buffer[512];
extern FILE *yyin;
extern char *yytext;
/* End */

static ProgramNode *root;

struct id_info{
    string name;
    uint32_t line_number;
    uint32_t col_number;
};

extern "C" int yylex(void);
static void yyerror(const char *msg);
extern int yylex_destroy(void);
%}

%code requires {
    #include "include/AST/ast.hpp"
    #include "include/AST/assignment.hpp"
    #include "include/AST/BinaryOperator.hpp"
    #include "include/AST/CompoundStatement.hpp"
    #include "include/AST/ConstantValue.hpp"
    #include "include/AST/decl.hpp"
    #include "include/AST/expression.hpp"
    #include "include/AST/for.hpp"
    #include "include/AST/function.hpp"
    #include "include/AST/FunctionInvocation.hpp"
    #include "include/AST/if.hpp"
    #include "include/AST/print.hpp"
    #include "include/AST/program.hpp"
    #include "include/AST/read.hpp"
    #include "include/AST/return.hpp"
    #include "include/AST/UnaryOperator.hpp"
    #include "include/AST/variable.hpp"
    #include "include/AST/VariableReference.hpp"
    #include "include/AST/while.hpp"
}

    /* For yylval */
%union {
    /* basic semantic value */
    char *identifier;
    int valueInt;
    float valueFloat;
    Node node;
    Nodevec* Nodevecptr;
    vector<struct id_info>* id_infoptr;
    VariableInfo* Var_info;
    struct NodeWithTypeList* arg_ptr;
    struct std::vector<NodeWithTypeList*>* argvec_ptr;
    enum enumoperator op_type;
};

%type <identifier> ProgramName ID;
%type <identifier> FunctionName;
%type <identifier> NegOrNot;

%type <Nodevecptr> FunctionList;
%type <Nodevecptr> Functions;
%type <node> Function;
%type <node> FunctionDeclaration;
%type <node> FunctionDefinition;
%type <argvec_ptr> FormalArgList;
%type <argvec_ptr> FormalArgs;
%type <arg_ptr> FormalArg;

%type <Nodevecptr> DeclarationList;
%type <Nodevecptr> Declarations;
%type <node> Declaration;

%type <node> CompoundStatement;
%type <Nodevecptr> StatementList;
%type <Nodevecptr> Statements;
%type <node> Statement;
%type <node> Simple;
%type <node> Condition;
%type <node> While;
%type <node> For;
%type <node> Return;
%type <node> FunctionCall;
%type <node> FunctionInvocation;

%type <node> VariableReference;
%type <node> Expression;
%type <Nodevecptr> Expressions;
%type <Nodevecptr> ExpressionList;
%type <node> ElseOrNot;

%type <Nodevecptr> ArrRefList;
%type <Nodevecptr> ArrRefs;


%type <id_infoptr> IdList;
%type <Var_info> Type;
%type <Var_info> ScalarType;
%type <Var_info> ArrType;
%type <Var_info> ArrDecl;
%type <Var_info> LiteralConstant;
%type <Var_info> IntegerAndReal;
%type <Var_info> StringAndBoolean;
%type <Var_info> ReturnType;

%type <valueInt> INT_LITERAL;
%type <valueFloat> REAL_LITERAL;
%type <identifier> STRING_LITERAL;
%type <identifier> TRUE;
%type <identifier> FALSE;


    /* Delimiter */
%token COMMA SEMICOLON COLON
%token L_PARENTHESIS R_PARENTHESIS
%token L_BRACKET R_BRACKET

    /* Operator */
%token <op_type> ASSIGN
%left <op_type> OR
%left <op_type> AND
%right <op_type> NOT
%left <op_type> LESS LESS_OR_EQUAL EQUAL GREATER GREATER_OR_EQUAL NOT_EQUAL
%left <op_type> PLUS MINUS
%left <op_type> MULTIPLY DIVIDE MOD
%right <op_type> UNARY_MINUS

    /* Keyword */
%token ARRAY BOOLEAN INTEGER REAL STRING
%token END BEGIN_ /* Use BEGIN_ since BEGIN is a keyword in lex */
%token DO ELSE FOR IF THEN WHILE
%token DEF OF TO RETURN VAR
%token FALSE TRUE
%token PRINT READ

    /* Identifier */
%token ID

    /* Literal */
%token INT_LITERAL
%token REAL_LITERAL
%token STRING_LITERAL

%%
    /*
       Program Units
                     */

Program:
    ProgramName SEMICOLON
    /* ProgramBody */
    DeclarationList FunctionList CompoundStatement
    /* End of ProgramBody */
    END {
        root = new ProgramNode(@1.first_line, @1.first_column, $1, $3, $4, $5);
        //$4, , $5
    }
;

ProgramName:
    ID 
;

DeclarationList:
    Epsilon { $$ = nullptr; }
    |
    Declarations { $$ = $1; }
;

Declarations:
    Declaration {
        $$ = new Nodevec();
        $$->push_back($1);
    }
    |
    Declarations Declaration {
        $1->push_back($2);
        $$ = $1;
    }
;

FunctionList:
    Epsilon {$$ = nullptr; }
    |
    Functions { $$ = $1; }
;

Functions:
    Function {
        $$ = new Nodevec();
        $$->push_back($1);
    }
    |
    Functions Function {
        $1->push_back($2);
        $$ = $1;
    }
;

Function:
    FunctionDeclaration { $$ = $1; }
    |
    FunctionDefinition { $$ = $1; }
;

FunctionDeclaration:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType SEMICOLON {
        std::vector<VariableInfo*> arg_list;
        if($3!=nullptr){
            for(int i=0;i<$3->size();i++){
                for(int j=0;j<(*$3)[i]->counter;j++){
                    VariableInfo* Tem = new VariableInfo();
                    Tem->type_set = (*$3)[i]->type->type_set;
                    Tem->type = (*$3)[i]->type->type;
                    Tem->array_val = (*$3)[i]->type->array_val;
                    Tem->int_lit = (*$3)[i]->type->int_lit;
                    Tem->real_lit = (*$3)[i]->type->real_lit;
                    Tem->string_lit = (*$3)[i]->type->string_lit;
                    Tem->boolean_lit = (*$3)[i]->type->boolean_lit;
                    arg_list.push_back(Tem);
                }
            }
        }
        $$ = new FunctionNode(@1.first_line, @1.first_column, string($1), $3, $5, nullptr, arg_list);
    }
;

FunctionDefinition:
    FunctionName L_PARENTHESIS FormalArgList R_PARENTHESIS ReturnType
    CompoundStatement
    END {
        std::vector<VariableInfo*> arg_list;
        if($3!=nullptr){
            for(int i=0;i<$3->size();i++){
                for(int j=0;j<(*$3)[i]->counter;j++){
                    VariableInfo* Tem = new VariableInfo();
                    Tem->type_set = (*$3)[i]->type->type_set;
                    Tem->type = (*$3)[i]->type->type;
                    Tem->array_val = (*$3)[i]->type->array_val;
                    Tem->int_lit = (*$3)[i]->type->int_lit;
                    Tem->real_lit = (*$3)[i]->type->real_lit;
                    Tem->string_lit = (*$3)[i]->type->string_lit;
                    Tem->boolean_lit = (*$3)[i]->type->boolean_lit;
                    arg_list.push_back(Tem);
                }
            }
        }
        $$ = new FunctionNode(@1.first_line, @1.first_column, string($1), $3, $5, $6, arg_list);
    }
;

FunctionName:
    ID
;

FormalArgList:
    Epsilon { $$ = nullptr; }
    |
    FormalArgs {
        $$ = $1;
    }
;

FormalArgs:
    FormalArg {
        $$ = new std::vector<NodeWithTypeList*>();
        $$->push_back($1);
    } 
    |
    FormalArgs SEMICOLON FormalArg {
        $1->push_back($3);
        $$ = $1; 
    }
;

FormalArg:
    IdList COLON Type {
        $$ = new NodeWithTypeList();
        $$->type = $3;
        $$->counter = 0;
        Nodevec* var_list = new Nodevec();
        for(int i=0;i<$1->size();i++){
            VariableInfo* Tem = new VariableInfo();
            Tem->type_set = $3->type_set;
            Tem->type = $3->type;
            Tem->array_val = $3->array_val;
            Tem->int_lit = $3->int_lit;
            Tem->real_lit = $3->real_lit;
            Tem->string_lit = $3->string_lit;
            Tem->boolean_lit = $3->boolean_lit;
            VariableNode *var_node = new VariableNode(
                (*$1)[i].line_number, (*$1)[i].col_number,
                (*$1)[i].name, Tem, nullptr
            );
            var_list->push_back(var_node);
            $$->counter++;
        }
        $$->node = new DeclNode(@1.first_line, @1.first_column, var_list);
    }
;

IdList:
    ID {
        $$ = new std::vector<id_info>();
        $$->push_back( id_info{string($1), @1.first_line, @1.first_column} );

        free($1);
    }
    |
    IdList COMMA ID{
        $1->push_back( id_info{string($3), @3.first_line, @3.first_column} );
        $$ = $1;

        free($3);
    }
;

ReturnType:
    COLON ScalarType {
        $$ = new VariableInfo();
        $$->type_set = $2->type_set;
        $$->type = $2->type;
    }
    |
    Epsilon {
        $$ = new VariableInfo();
        $$->type_set = UNKNOWN_SET;
        $$->type = TYPE_VOID;
    }
;

    /*
       Data Types and Declarations
                                   */

Declaration:
    VAR IdList COLON Type SEMICOLON{
        Nodevec* var_list = new Nodevec();
        for(int i=0;i<$2->size();i++){
            VariableInfo* Tem = new VariableInfo();
            Tem->type_set = $4->type_set;
            Tem->type = $4->type;
            Tem->array_val = $4->array_val;
            Tem->int_lit = $4->int_lit;
            Tem->real_lit = $4->real_lit;
            Tem->string_lit = $4->string_lit;
            Tem->boolean_lit = $4->boolean_lit;
            VariableNode *var_node = new VariableNode(
                (*$2)[i].line_number, (*$2)[i].col_number,
                (*$2)[i].name, Tem, nullptr
            );
            var_list->push_back(var_node);
        }
        $$ = new DeclNode(@1.first_line, @1.first_column, var_list);
    }
    |
    VAR IdList COLON LiteralConstant SEMICOLON{
        Nodevec* var_list = new Nodevec();
        for(int i=0;i<$2->size();i++){
            VariableInfo* Tem = new VariableInfo();
            Tem->type_set = $4->type_set;
            Tem->type = $4->type;
            Tem->array_val = $4->array_val;
            Tem->int_lit = $4->int_lit;
            Tem->real_lit = $4->real_lit;
            Tem->string_lit = $4->string_lit;
            Tem->boolean_lit = $4->boolean_lit;
            
            ConstantValueNode *const_node = new ConstantValueNode(
                @3.first_line, (@3.first_column+2), Tem
            );

            VariableInfo* Tem2 = new VariableInfo();
            Tem2->type_set = $4->type_set;
            Tem2->type = $4->type;
            Tem2->array_val = $4->array_val;
            Tem2->int_lit = $4->int_lit;
            Tem2->real_lit = $4->real_lit;
            Tem2->string_lit = $4->string_lit;
            Tem2->boolean_lit = $4->boolean_lit;

            VariableNode *var_node = new VariableNode(
                (*$2)[i].line_number, (*$2)[i].col_number,
                (*$2)[i].name, Tem2, const_node
            );
            var_list->push_back(var_node);
        }
        $$ = new DeclNode(@1.first_line, @1.first_column, var_list);
    }
;

Type:
    ScalarType { $$ = $1; }
    |
    ArrType { $$ = $1; }
;

ScalarType:
    INTEGER { 
        $$ = new VariableInfo();
        $$->type_set = SET_SCALAR;
        $$->type = TYPE_INT;
    }
    |
    REAL { 
        $$ = new VariableInfo();
        $$->type_set = SET_SCALAR;
        $$->type = TYPE_REAL;
    }
    |
    STRING { 
        $$ = new VariableInfo();
        $$->type_set = SET_SCALAR;
        $$->type = TYPE_STRING;
    }
    |
    BOOLEAN { 
        $$ = new VariableInfo();
        $$->type_set = SET_SCALAR;
        $$->type = TYPE_BOOLEAN;
    }
;

ArrType:
    ArrDecl ScalarType {
        $$ = new VariableInfo();
        $$->type_set = SET_ARR;
        $$->type = $2->type;
        $$->array_val = $1->array_val;
    }
;

ArrDecl:
    ARRAY INT_LITERAL OF {
        $$ = new VariableInfo();
        $$->type_set = SET_ARR;
        $$->type = UNKNOWN_TYPE;
        $$->array_val.push_back($2);
    }
    |
    ArrDecl ARRAY INT_LITERAL OF{
        $1->array_val.push_back($3);
        $$ = $1;
    }
;

LiteralConstant:
    NegOrNot INT_LITERAL{
        $$ = new VariableInfo();
        $$->type_set = SET_CONST_LIT;
        $$->type = TYPE_INT;
        if($1=="-"){
            $$->int_lit = $2*(-1);
        }
        else {
            $$->int_lit = $2;
        }
    }
    |
    NegOrNot REAL_LITERAL{
        $$ = new VariableInfo();
        $$->type_set = SET_CONST_LIT;
        $$->type = TYPE_REAL;
        if($1=="-"){
            $$->real_lit = $2*(-1);
        }
        else {
            $$->real_lit = $2;
        }
    }
    |
    StringAndBoolean { 
        $$ = new VariableInfo();    
        $$->type_set = $1->type_set;
        $$->type = $1->type;
        $$->string_lit = $1->string_lit;
        $$->boolean_lit = $1->boolean_lit;
    }
;


NegOrNot:
    Epsilon { $$ = nullptr; }
    |
    MINUS %prec UNARY_MINUS{
        $$ = "-";
    }
;

StringAndBoolean:
    STRING_LITERAL { 
        $$ = new VariableInfo();
        $$->type_set = SET_CONST_LIT;
        $$->type = TYPE_STRING;
        $$->string_lit = string($1);
        
    }
    |
    TRUE { 
        $$ = new VariableInfo();
        $$->type_set = SET_CONST_LIT;
        $$->type = TYPE_BOOLEAN;
        $$->boolean_lit = Boolean_TRUE;
    }
    |
    FALSE { 
        $$ = new VariableInfo();
        $$->type_set = SET_CONST_LIT;
        $$->type = TYPE_BOOLEAN;
        $$->boolean_lit = Boolean_FALSE;
    }
;

IntegerAndReal:
    INT_LITERAL {
        $$ = new VariableInfo();
        $$->type_set = SET_CONST_LIT;
        $$->type = TYPE_INT;
        $$->int_lit = $1;
    }
    |
    REAL_LITERAL {
        $$ = new VariableInfo();
        $$->type_set = SET_CONST_LIT;
        $$->type = TYPE_REAL;
        $$->real_lit = $1;
    }
;

    /*
       Statements
                  */

Statement:
    CompoundStatement {$$ = $1;}
    |
    Simple {$$ = $1;}
    |
    Condition {$$ = $1;}
    |
    While {$$ = $1;}
    |
    For {$$ = $1;}
    |
    Return {$$ = $1;}
    |
    FunctionCall {$$ = $1;}
;

CompoundStatement:
    BEGIN_
    DeclarationList
    StatementList
    END {
        $$ = new CompoundStatementNode(@1.first_line, @1.first_column, $2, $3);
    }
;

Simple:
    VariableReference ASSIGN Expression SEMICOLON {
        $$ = new AssignmentNode(@2.first_line, @2.first_column, $1, $3);
    }
    |
    PRINT Expression SEMICOLON {
        $$ = new PrintNode(@1.first_line, @1.first_column, $2);
    }
    |
    READ VariableReference SEMICOLON {
        $$ = new ReadNode(@1.first_line, @1.first_column, $2);
    }
;

VariableReference:
    ID ArrRefList {
        $$ = new VariableReferenceNode(@1.first_line, @1.first_column, string($1), $2);
    }
;

ArrRefList:
    Epsilon {$$ = nullptr;}
    |
    ArrRefs {
        $$ = $1;
    }
;

ArrRefs:
    L_BRACKET Expression R_BRACKET{
        $$ = new Nodevec();
        $$->push_back($2);
    }
    |
    ArrRefs L_BRACKET Expression R_BRACKET{
        $1->push_back($3);
        $$ = $1;
    }
;

Condition:
    IF Expression THEN
    CompoundStatement
    ElseOrNot
    END IF{
        $$ = new IfNode(@1.first_line, @1.first_column, $2, $4, $5);
    }
;

ElseOrNot:
    ELSE
    CompoundStatement {
        $$ = $2;
    }
    |
    Epsilon {$$ = nullptr;}
;

While:
    WHILE Expression DO
    CompoundStatement
    END DO {
        $$ = new WhileNode(@1.first_line, @1.first_column, $2, $4);
    }
;

For:
    FOR ID ASSIGN INT_LITERAL TO INT_LITERAL DO
    CompoundStatement
    END DO {
        VariableInfo* var_info = new VariableInfo();
        var_info->type_set = SET_SCALAR;
        var_info->type = TYPE_INT;

        VariableNode* var_node = new VariableNode(@2.first_line, @2.first_column, $2, 
                                                    var_info, nullptr);

        Nodevec* var_list = new Nodevec();
        var_list->push_back(var_node);
        DeclNode* decl_node = new DeclNode(@2.first_line, @2.first_column, var_list);

        VariableReferenceNode* var_ref_node = new VariableReferenceNode(@2.first_line, @2.first_column,
                                                                        $2, nullptr);
        
        VariableInfo* var_info2 = new VariableInfo();
        var_info2->type_set = SET_SCALAR;
        var_info2->type = TYPE_INT;
        var_info2->int_lit = $4;
        ConstantValueNode* const_node = new ConstantValueNode(@4.first_line, @4.first_column, var_info2);

        AssignmentNode* assign_node = new AssignmentNode(@3.first_line, @3.first_column, 
                                                        var_ref_node, const_node);

        VariableInfo* var_info3 = new VariableInfo();
        var_info3->type_set = SET_SCALAR;
        var_info3->type = TYPE_INT;
        var_info3->int_lit = $6;
        ConstantValueNode* const_node2 = new ConstantValueNode(@6.first_line, @6.first_column, var_info3);

        $$ = new ForNode(@1.first_line, @1.first_column, decl_node, assign_node,
                        const_node2, $8);
    }
;

Return:
    RETURN Expression SEMICOLON {
        $$ = new ReturnNode(@1.first_line, @1.first_column, $2);
    }
;

FunctionCall:
    FunctionInvocation SEMICOLON {
        $$ = $1;
    }
;

FunctionInvocation:
    ID L_PARENTHESIS ExpressionList R_PARENTHESIS {
        $$ = new FunctionInvocationNode(@1.first_line, @1.first_column, $1, $3);
    }
;

ExpressionList:
    Epsilon {$$ = nullptr;}
    |
    Expressions {$$ = $1;}
;

Expressions:
    Expression {
        $$ = new Nodevec();
        $$->push_back($1);
    }
    |
    Expressions COMMA Expression{
        $1->push_back($3);
        $$ = $1;
    }
;

StatementList:
    Epsilon { $$ = nullptr; }
    |
    Statements { $$ = $1; }
;

Statements:
    Statement {
        $$ = new Nodevec();
        $$->push_back($1);
    }
    |
    Statements Statement {
        $1->push_back($2);
        $$ = $1;
    }
;

Expression:
    L_PARENTHESIS Expression R_PARENTHESIS{ $$ = $2; }
    |
    MINUS Expression %prec UNARY_MINUS{
        $$ = new UnaryOperatorNode(@1.first_line, @1.first_column, $1, $2);
    }
    |
    Expression MULTIPLY Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression DIVIDE Expression {
        
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression MOD Expression {
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression PLUS Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression MINUS Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression LESS Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression LESS_OR_EQUAL Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression GREATER Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression GREATER_OR_EQUAL Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression EQUAL Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression NOT_EQUAL Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    NOT Expression{
        $$ = new UnaryOperatorNode(@1.first_line, @1.first_column, $1, $2);
    }
    |
    Expression AND Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    Expression OR Expression{
        $$ = new BinaryOperatorNode(@2.first_line, @2.first_column, $1, $2, $3);
    }
    |
    IntegerAndReal {
        $$ = new ConstantValueNode(@1.first_line, @1.first_column, $1);
    }
    |
    StringAndBoolean {
        $$ = new ConstantValueNode(@1.first_line, @1.first_column, $1);
    }
    |
    VariableReference {$$ = $1;}
    |
    FunctionInvocation {$$ = $1;}
;

    /*
       misc
            */
Epsilon: 
;
%%

void yyerror(const char *msg) {
    fprintf(stderr,
            "\n"
            "|-----------------------------------------------------------------"
            "---------\n"
            "| Error found in Line #%d: %s\n"
            "|\n"
            "| Unmatched token: %s\n"
            "|-----------------------------------------------------------------"
            "---------\n",
            line_num, buffer, yytext);
    exit(-1);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./parser <filename> [--dump-ast]\n");
        exit(-1);
    }

    yyin = fopen(argv[1], "r");
    assert(yyin != NULL && "fopen() fails.");

    yyparse();

    if (argc >= 3 && strcmp(argv[2], "--dump-ast") == 0) {
        root->print();
    }

    printf("\n"
           "|--------------------------------|\n"
           "|  There is no syntactic error!  |\n"
           "|--------------------------------|\n");

    delete root;
    fclose(yyin);
    yylex_destroy();
    return 0;
}
