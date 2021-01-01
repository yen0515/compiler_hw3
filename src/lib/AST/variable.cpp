#include "AST/variable.hpp"
#include <vector>

// TODO
VariableNode::VariableNode(const uint32_t line, const uint32_t col, string v_name,
                             VariableInfo *v_type, Node _const_node)
    : AstNode{line, col}, name(v_name), type(v_type), const_node(_const_node) {}


// TODO: You may use code snippets in AstDumper.cpp
void VariableNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("variable <line: %u, col: %u> %s %s\n",
                location.line, location.col,
                name.c_str(), this->gettype().c_str());
    visitChildNodes();
}

void VariableNode::visitChildNodes() {
    if(const_node!=nullptr){
        //std::printf("      ");
        const_node->spacecounter = this->spacecounter+1;;
        const_node->print();
    }
    
}

std::string VariableNode::gettype(){
    if(this->type->type_set == SET_SCALAR){
        if(this->type->type == TYPE_INT) this->var_type = "integer";
        else if(this->type->type == TYPE_REAL) this->var_type = "real";
        else if(this->type->type == TYPE_STRING) this->var_type = "string";
        else if(this->type->type == TYPE_BOOLEAN) this->var_type = "boolean";
    }
    else if(this->type->type_set == SET_CONST_LIT) {
        if(this->type->type == TYPE_INT) this->var_type = "integer";
        else if(this->type->type == TYPE_REAL) this->var_type = "real";
        else if(this->type->type == TYPE_STRING) this->var_type = "string";
        else if(this->type->type == TYPE_BOOLEAN) this->var_type = "boolean";
    }
    else if(this->type->type_set == SET_ARR) {
        if(this->type->type == TYPE_INT) this->var_type = "integer ";
        else if(this->type->type == TYPE_REAL) this->var_type = "real ";
        else if(this->type->type == TYPE_STRING) this->var_type = "string ";
        else if(this->type->type == TYPE_BOOLEAN) this->var_type = "boolean ";
        else this->var_type = "unknown";

        for(int i=0;i<this->type->array_val.size();i++){
            this->var_type += "[";
            this->var_type += std::to_string(this->type->array_val[i]);
            this->var_type += "]";
        }
    }
    return this->var_type;
}