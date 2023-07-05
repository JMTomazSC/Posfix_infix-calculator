#ifndef expressao
#define expressao

#include <iostream>
#include <string>
#include <sstream>
#include "Stack.hpp"

using namespace std;


class Expression{

public:

//Construtor
Expression();

//Faz a leitura da expressão e determina se ela será ou não armazenada
void read_infix_expression(string op);

void read_posfix_expression(string op);

//Analisa se a expressão é válida
bool is_valid_infixexpression(string op);

bool is_valid_posfixexpression(string op);

//Avalia se a expressão é posfixa
bool isPosfix(string op);

//Converte a expressão para posfixa
string to_posfix(string op);

//Converte a expressão para infixa
string to_infix(string op);

//Resolve a expressão
void solve(string value);

//Destroi a expressão
void destruct();

//Utiliza de recursão para retornar o valor armazenado de cada no da arvore
double recursion(node* s);

//Verifica se o valor representado pela string pode ser escrito como um double
bool double_number(string& op);


private:
    //Função que retorna se o parâmetro passado é um operador matématico ou não
    bool is_operator(char c){
        return(c == '+' || c == '-' || c == '*' || c == '/');
    }
    //Função que retorna um valor para definir a precedência dos operadores de acordo com a matemática
    int precedence(char op){
        if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
        return 0;
    }

    Stack<string> auxiliar;
};

//Excessão que será emitida pelo programa caso a expressão não seja válida
struct not_valid_expression{
    string expression;
};

//Excessão que será emitada pelo programa caso a expressão não esteja armazenada
struct not_exist_expression{
    string expression;
};

struct zero_division{
    float number;
};










#endif