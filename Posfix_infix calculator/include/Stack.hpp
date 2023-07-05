#ifndef Stack_h
#define Stack_h
#include <string>
#include <iostream>
#include "Node.hpp"
#define MAXTAM 100

using namespace std;

template <typename S>
class Stack{
    public:
    //Construtor
    Stack();

    //Adiciona um elemento no topo da pilha
    void Empilha(S value);

    //Retira o elemento do topo da pilha
    S Desempilha();

    //Verifica se a Stackestá vazia
    bool Vazia();

    //Verifica se a Stackestá cheia
    bool Cheia();
    //Destroi a pilha
    void Destroi();

    S get_top();

    //Retorna o tamanho da pilha
    int size();




    private:
    int top;
    S data[MAXTAM];
};

// Metódo construtor
template <typename S>
Stack<S>::Stack(){
    top = -1;
}
template <typename S>
bool Stack<S>::Cheia(){
    return top == MAXTAM - 1;
}

//Adiciona um elemento na pilha
template <typename S>
void Stack<S>::Empilha(S value){
    if(!Cheia()){
        top++;
        data[top] = value;
    }
}

//Retira o elemento do topo da pilha
template <typename S>
S Stack<S>:: Desempilha(){
    if(!Vazia()){
        S value = data[top];
        top--;
        return value;
    }else{
        return S();
    }

}

// Verifica se a Stack está vazia
template <typename S>
bool Stack<S>:: Vazia(){
    return top == -1;
}
//Destrutor
template <typename S>
void Stack<S>::Destroi(){
    while(!Vazia()){
        Desempilha();
    }
}
//Retorna o valor no topo da pilha
template <typename S>
S Stack<S>::get_top(){
    if(!Vazia()){
        return data[top];
    }else{
        return S();
    }
}
//Retorna o tamanho da pilha
template <typename S>
int Stack<S>::size(){
    return top + 1;
}




#endif