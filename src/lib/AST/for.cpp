#include "AST/for.hpp"

// TODO
ForNode::ForNode(const uint32_t line, const uint32_t col,
                Node _decl_node, Node _assign_node, Node _const_node,
                Node _comp)
    : AstNode{line, col}, decl_node(_decl_node), assign_node(_assign_node),
        const_node(_const_node), comp(_comp) {}

// TODO: You may use code snippets in AstDumper.cpp
void ForNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("for statement <line: %u, col: %u>\n",
    location.line, location.col);

    visitChildNodes();
}

void ForNode::visitChildNodes() {
    if(this->decl_node!=nullptr){
        this->decl_node->spacecounter = this->spacecounter+1;
        this->decl_node->print();
    }
    if(this->assign_node!=nullptr){
        this->assign_node->spacecounter = this->spacecounter+1;
        this->assign_node->print();
    }
    if(this->const_node!=nullptr){
        this->const_node->spacecounter = this->spacecounter+1;
        this->const_node->print();
    }
    if(this->comp!=nullptr){
        this->comp->spacecounter = this->spacecounter+1;
        this->comp->print();
    }
}
