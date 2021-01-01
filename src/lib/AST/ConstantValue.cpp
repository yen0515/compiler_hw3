#include "AST/ConstantValue.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

// TODO
ConstantValueNode::ConstantValueNode(const uint32_t line, const uint32_t col, VariableInfo *_const_val)
    : ExpressionNode{line, col}, const_val(_const_val) {}


// TODO: You may use code snippets in AstDumper.cpp
void ConstantValueNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::cout<<"constant <line: "<<location.line<<", col: "<<location.col<<"> "
            <<this->getval()<<std::endl;
    /*std::cout<<"constant <line: "<<location.line<<", col: "<<location.col<<"> ";

    getval(); */  
}

std::string ConstantValueNode::getval(){
    if(this->const_val->type == TYPE_INT) val = to_string(this->const_val->int_lit);
    else if(this->const_val->type == TYPE_REAL) val = to_string(this->const_val->real_lit);
    else if(this->const_val->type == TYPE_STRING) {
        val = this->const_val->string_lit;
        val.erase(0,1);
        val.erase(val.length()-1,1);
    }
    else if(this->const_val->type == TYPE_BOOLEAN) {
        if(this->const_val->boolean_lit == Boolean_TRUE) val = "true";
        else if(this->const_val->boolean_lit == Boolean_FALSE) val = "false";
    }

    return val; 
}

/*void ConstantValueNode::setspace(int newspace){
    this->space_counter = newspace;
}*/