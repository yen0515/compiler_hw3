#include "AST/FunctionInvocation.hpp"

// TODO
FunctionInvocationNode::FunctionInvocationNode(const uint32_t line, const uint32_t col,
                                                std::string f_name, Nodevec *_exp_list)
    : ExpressionNode{line, col}, name(f_name), exp_list(_exp_list) {}

// TODO: You may use code snippets in AstDumper.cpp
void FunctionInvocationNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("function invocation <line: %u, col: %u> %s\n",
                location.line, location.col, this->name.c_str());
    visitChildNodes();
}

void FunctionInvocationNode::visitChildNodes() {
    if(exp_list!=nullptr){
        for(int i=0;i<exp_list->size();i++){
            (*this->exp_list)[i]->spacecounter = this->spacecounter+1;
            (*this->exp_list)[i]->print();
        }
    }
}
