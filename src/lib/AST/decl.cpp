#include "AST/decl.hpp"
#include <vector>

// TODO
DeclNode::DeclNode(const uint32_t line, const uint32_t col, Nodevec* _var_node_vec)
    : AstNode{line, col}, var_node_vec(_var_node_vec) {}

// TODO
//DeclNode::DeclNode(const uint32_t line, const uint32_t col)
//    : AstNode{line, col} {}

// TODO: You may use code snippets in AstDumper.cpp
void DeclNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("declaration <line: %u, col: %u>\n",
                location.line, location.col);
    visitChildNodes();
}

void DeclNode::visitChildNodes() {
    if(var_node_vec!=nullptr){
        for(int i=0;i<var_node_vec->size();i++){
            //std::printf("    ");
            (*var_node_vec)[i]->spacecounter = this->spacecounter+1;
            (*var_node_vec)[i]->print();
        }
    }
}

/*void DeclNode::setspace(int newspace){
    this->space_counter = newspace;
}*/