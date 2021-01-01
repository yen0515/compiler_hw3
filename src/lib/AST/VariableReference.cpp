#include "AST/VariableReference.hpp"

// TODO
VariableReferenceNode::VariableReferenceNode(const uint32_t line, const uint32_t col,
                                            std::string v_name, Nodevec *_arr_ref)
    : ExpressionNode{line, col}, name(v_name), arr_ref(_arr_ref) {}


void VariableReferenceNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("variable reference <line: %u, col: %u> %s\n",
                location.line, location.col, name.c_str());
    visitChildNodes();
}

void VariableReferenceNode::visitChildNodes() {
    if(arr_ref!=nullptr){
        for(int i=0;i<arr_ref->size();i++){
            (*this->arr_ref)[i]->spacecounter = this->spacecounter+1;
            (*this->arr_ref)[i]->print();
        }
    }
}
