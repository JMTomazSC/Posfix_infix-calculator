#ifndef Node
#define Node

#include <string>
#include <iostream>
#include "Stack.hpp"

using namespace std;

class node {
public:
    string data;
    node* right;
    node* left;
    
    //Construtor
    node(string value){
        data = value;
        this->right = nullptr;
        this->left = nullptr;
    }
    //Destrutor
    void destruct(node* no){
        if(no == nullptr){
            return;
        }
        destruct(no->left);
        destruct(no->right);
        
        delete no;
    }
    
};


#endif
