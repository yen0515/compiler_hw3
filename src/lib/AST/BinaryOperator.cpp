#include "AST/BinaryOperator.hpp"

// TODO
BinaryOperatorNode::BinaryOperatorNode(const uint32_t line, const uint32_t col,
                                        Node _expression_fir, enumoperator _op,
                                        Node _expression_sec)
    : ExpressionNode{line, col}, expression_fir(_expression_fir), 
        op(_op), expression_sec(_expression_sec) {}

// TODO: You may use code snippets in AstDumper.cpp
void BinaryOperatorNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("binary operator <line: %u, col: %u> %s\n",
                location.line, location.col, this->getop().c_str());
    //std::printf("yes!!! %s\n", this->op_str.c_str());
    visitChildNodes();
}

void BinaryOperatorNode::visitChildNodes() {
    if(expression_fir!=nullptr){
        this->expression_fir->spacecounter = this->spacecounter+1;
        this->expression_fir->print();
    }
    if(expression_sec!=nullptr){
        this->expression_sec->spacecounter = this->spacecounter+1;
        this->expression_sec->print();
    }
}

std::string BinaryOperatorNode::getop(){
    if(this->op == OP_OR) this->op_str = "or";
    else if(this->op == OP_AND) this->op_str = "and";
    else if(this->op == OP_LESS) this->op_str = "<";
    else if(this->op == OP_LESS_OR_EQUAL) this->op_str = "<=";
    else if(this->op == OP_EQUAL) this->op_str = "=";
    else if(this->op == OP_GREATER) this->op_str = ">";
    else if(this->op == OP_GREATER_OR_EQUAL) this->op_str = ">=";
    else if(this->op == OP_NOT_EQUAL) this->op_str = "<>";
    else if(this->op == OP_PLUS) this->op_str = "+";
    else if(this->op == OP_MINUS) this->op_str = "-";
    else if(this->op == OP_MULTIPLY) this->op_str = "*";
    else if(this->op == OP_DIVIDE) this->op_str = "/";
    else if(this->op == OP_MOD) this->op_str = "mod";
    else this->op_str = "error";

    return this->op_str;
}

