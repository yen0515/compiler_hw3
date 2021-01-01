#include "AST/function.hpp"

// TODO
FunctionNode::FunctionNode(const uint32_t line, const uint32_t col,
                            std::string f_name, std::vector <NodeWithTypeList*>*  _argvec,
                            VariableInfo *_returntype, Node _comp_node,
                            std::vector <VariableInfo*> _arglist)
    : AstNode{line, col}, name(f_name), argvec(_argvec), 
        returntype(_returntype), comp_node(_comp_node), arglist(_arglist) {}

// TODO: You may use code snippets in AstDumper.cpp
void FunctionNode::print() {
    for(int i=0;i<2*spacecounter;i++){
        printf(" ");
    }
    std::printf("function declaration <line: %u, col: %u> %s %s %s\n",
                location.line, location.col, name.c_str(), this->get_returntype().c_str(),
                this->get_argtype().c_str());
    visitChildNodes();
}

void FunctionNode::visitChildNodes(){
    if(argvec!=nullptr){
        for(int i=0;i<argvec->size();i++){
            (*argvec)[i]->node->spacecounter = this->spacecounter+1;
            (*argvec)[i]->node->print();
        }
    }
    if(this->comp_node!=NULL){
        //std::printf("  ");
        this->comp_node->spacecounter = this->spacecounter+1;
        this->comp_node->print();
    } 
}

/*void FunctionNode::setspace(int newspace){
    this->space_counter = newspace;
}*/

std::string FunctionNode::get_returntype(){
    if(returntype->type_set == SET_SCALAR){
        if(returntype->type == TYPE_INT) this->returntype_str = "integer";
        else if(returntype->type == TYPE_REAL) this->returntype_str = "real";
        else if(returntype->type == TYPE_STRING) this->returntype_str = "string";
        else if(returntype->type == TYPE_BOOLEAN) this->returntype_str = "boolean";
    }
    else if(returntype->type_set == UNKNOWN_SET){
        if(returntype->type == TYPE_VOID) this->returntype_str = "void";
    }
    else this->returntype_str = "error";

    return this->returntype_str;
}

std::string FunctionNode::get_argtype(){
    if(this->arglist.size()==0) this->argtype = "()";
    else if(this->arglist.size()==1) {
        this->argtype = "(";
        if(this->arglist[0]->type_set == SET_SCALAR){
            if(this->arglist[0]->type == TYPE_INT) this->argtype += "integer";
            else if(this->arglist[0]->type == TYPE_REAL) this->argtype += "real";
            else if(this->arglist[0]->type == TYPE_STRING) this->argtype += "string";
            else if(this->arglist[0]->type == TYPE_BOOLEAN) this->argtype += "boolean";
        }
        else if(this->arglist[0]->type_set == SET_ARR){
            if(this->arglist[0]->type == TYPE_INT) this->argtype += "integer ";
            else if(this->arglist[0]->type == TYPE_REAL) this->argtype += "real ";
            else if(this->arglist[0]->type == TYPE_STRING) this->argtype += "string ";
            else if(this->arglist[0]->type == TYPE_BOOLEAN) this->argtype += "boolean ";

            for(int j=0;j<this->arglist[0]->array_val.size();j++){
                this->argtype += "[";
                this->argtype += std::to_string(this->arglist[0]->array_val[j]);
                this->argtype += "]";
            }
        }
        this->argtype += ")";
    }
    else{
        this->argtype = "(";
        for(int i=0;i<this->arglist.size()-1;i++){
            if(this->arglist[i]->type_set == SET_SCALAR){
                if(this->arglist[i]->type == TYPE_INT) this->argtype += "integer";
                else if(this->arglist[i]->type == TYPE_REAL) this->argtype += "real";
                else if(this->arglist[i]->type == TYPE_STRING) this->argtype += "string";
                else if(this->arglist[i]->type == TYPE_BOOLEAN) this->argtype += "boolean";
            }
            else if(this->arglist[i]->type_set == SET_ARR){
                if(this->arglist[i]->type == TYPE_INT) this->argtype += "integer ";
                else if(this->arglist[i]->type == TYPE_REAL) this->argtype += "real ";
                else if(this->arglist[i]->type == TYPE_STRING) this->argtype += "string ";
                else if(this->arglist[i]->type == TYPE_BOOLEAN) this->argtype += "boolean ";

                for(int j=0;j<this->arglist[i]->array_val.size();j++){
                    this->argtype += "[";
                    this->argtype += std::to_string(this->arglist[i]->array_val[j]);
                    this->argtype += "]";
                }
            }
            this->argtype += ", ";
        }

        if(this->arglist[this->arglist.size()-1]->type_set == SET_SCALAR){
            if(this->arglist[this->arglist.size()-1]->type == TYPE_INT) this->argtype += "integer";
            else if(this->arglist[this->arglist.size()-1]->type == TYPE_REAL) this->argtype += "real";
            else if(this->arglist[this->arglist.size()-1]->type == TYPE_STRING) this->argtype += "string";
            else if(this->arglist[this->arglist.size()-1]->type == TYPE_BOOLEAN) this->argtype += "boolean";
        }
        else if(this->arglist[this->arglist.size()-1]->type_set == SET_ARR){
            if(this->arglist[this->arglist.size()-1]->type == TYPE_INT) this->argtype += "integer ";
            else if(this->arglist[this->arglist.size()-1]->type == TYPE_REAL) this->argtype += "real ";
            else if(this->arglist[this->arglist.size()-1]->type == TYPE_STRING) this->argtype += "string ";
            else if(this->arglist[this->arglist.size()-1]->type == TYPE_BOOLEAN) this->argtype += "boolean ";

            for(int j=0;j<this->arglist[this->arglist.size()-1]->array_val.size();j++){
                this->argtype += "[";
                this->argtype += std::to_string(this->arglist[this->arglist.size()-1]->array_val[j]);
                this->argtype += "]";
            }
        }
        this->argtype += ")";
    }
    return this->argtype;
}

// void FunctionNode::visitChildNodes(AstNodeVisitor &p_visitor) {
//     // TODO
// }
