#include "AST/program.hpp"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

// TODO
ProgramNode::ProgramNode(const uint32_t line, const uint32_t col,
                            std::string p_name, Nodevec *_decllist, 
                            Nodevec *_funclist, Node _comp_node )
    : AstNode{line, col}, name(p_name), decllist(_decllist),
        funclist(_funclist), comp_node(_comp_node){}

// visitor pattern version: const char *ProgramNode::getNameCString() const { return name.c_str(); }
//      
void ProgramNode::print() {
    std::printf("program <line: %u, col: %u> %s %s\n",
                location.line, location.col,
                name.c_str(), "void");
    this->spacecounter = 0;
    // TODO
    visitChildNodes();
}

void ProgramNode::visitChildNodes(){
    if(this->decllist!=nullptr){
        for(int i=0;i<this->decllist->size();i++){
            //std::printf("  ");
            (*this->decllist)[i]->spacecounter = this->spacecounter+1;
            (*this->decllist)[i]->print();
        }
    }
    if(this->funclist!=nullptr){
        for(int i=0;i<funclist->size();i++){
            //std::printf("  ");
            (*this->funclist)[i]->spacecounter = this->spacecounter+1;
            (*this->funclist)[i]->print();
        }
    }
    
    if(this->comp_node!=NULL){
        //std::printf("  ");
        this->comp_node->spacecounter = this->spacecounter+1;
        this->comp_node->print();
    } 
}

/*void ProgramNode::setspace(int newspace){
    this->space_counter = newspace;
}*/


/*void ProgramNode::visitChildNodes(AstNodeVisitor &p_visitor) { // visitor pattern version
    /* TODO
    *
    * for (auto &decl : var_decls) {
    *     decl->accept(p_visitor);    * }
    *
    * // functions
    *
    * body->accept(p_visitor);
    
    std::printf("  ");
    p_visitor.print();
    p_visitor.visitChildNodes(*this);
}*/
