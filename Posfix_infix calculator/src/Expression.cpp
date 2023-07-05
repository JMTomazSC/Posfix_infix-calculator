#include "../include/Stack.hpp"
#include <string>
#include "../include/Expression.hpp"
#include "../include/Node.hpp"
#define MAX_TAM 10

using namespace std;


//Construtor
Expression::Expression(){
}

//Função que lê e avalia se a expressão é válida e deve ser armazenada
void Expression::read_infix_expression(string op){
    
    if(is_valid_infixexpression(op)){
        cout << "EXPRESSAO OK: " << op << endl;
    }else{
        not_valid_expression error;
        error.expression = op;
        throw error;
    }
    
}
void Expression::read_posfix_expression(string op){
   if(is_valid_posfixexpression(op)){
        cout << "EXPRESSAO OK: " << op << endl;
    }else{
        not_valid_expression error;
        error.expression = op;
        throw error;
    }
}

bool Expression::is_valid_posfixexpression(string op){
    if(op.length() > 1000){
        not_valid_expression error1;
        error1.expression = op;
        throw error1;
        return false;
    }
    
    stringstream ss(op);
    string digit;
    int number = 0;
    int operador = 0;

    while(ss >> digit){
        if(digit != "+" && digit != "-" && digit != "*" && digit != "/" && !double_number(digit) && digit != "(" && digit != ")"){
            not_valid_expression error2;
            error2.expression = op;
            throw error2;
            return false;
            }
        if(double_number(digit)){
            number ++;
        }else if(is_operator(digit.c_str()[0])){
            if(number - operador < 2){
                not_valid_expression error;
                error.expression = op; 
                throw error;
            }
            operador++;
        }
        
    }
    if(number - 1 != operador){
        not_valid_expression error3;
        error3.expression = op;
        throw error3;
        return false;
    }
    return true;
    }
bool Expression::is_valid_infixexpression(string op){
    if(op.length() > 1000){
        not_valid_expression error1;
        error1.expression = op;
        throw error1;
        return false;
    }
    stringstream ss(op);
    string digit;
    int number = 0;
    int operador = 0;
    int parenteses = 0;

    while(ss >> digit){
        if(digit != "+" && digit != "-" && digit != "*" && digit != "/" && !double_number(digit) && digit != "(" && digit != ")"){
            not_valid_expression error2;
            error2.expression = op;
            throw error2;
            return false;
            }
        if(double_number(digit)){
            number ++;
        }else if(is_operator(digit.c_str()[0])){
            operador++;
        }else if(digit == "("){
            parenteses++;
        }else if(digit == ")"){
            parenteses--;
        }
    }
    if(number - 1 != operador){
        not_valid_expression error3;
        error3.expression = op;
        throw error3;
        return false;
    }
    if(parenteses != 0){
        not_valid_expression erro4;
        erro4.expression = op;
        throw erro4;
        return false;
    }
    return true;
    }



// Função que avalia se a expressão armazenada está em notação posfixa ou não
bool Expression::isPosfix(string op){
    int i = op.length() - 1;
    while(op[i] == ' '){
        i--;
    }
    if(is_operator(op[i])){
        return true;
    }
    return false;
}

//Função que verifica se o valor passado pela string pode ser escrito como uma variável double
bool Expression::double_number(string& op){
    try{
        double num = stod(op);
        num = num + 0;
        return true;
    }catch(const invalid_argument& error){
        return false;
    }
}

//Função responsável por converter a expressão armazenada para notação infixa
string Expression::to_infix(string op){
stringstream ss(op);
string digit;
    //Itera pela string armazenando em uma pilha os valores formatados de acordo com a notação
    while(ss >> digit){
        //Caso seja um digito, insere na pilha
        if(!is_operator(digit.c_str()[0])){
            auxiliar.Empilha(digit);
        //Caso seja um operador, salva os dois digitos anteriores, desempilha eles e empilha com parenteses e com o operador
        }else{
            string op1 = auxiliar.get_top();
            auxiliar.Desempilha();
            string op2 = auxiliar.get_top();
            auxiliar.Desempilha();
            string result = "( " + op2 + " " + digit + " " + op1 + " )" ;
            auxiliar.Empilha(result);
        }
    }
    //A string no topo da pilha será a forma da expressão em notação infixa
    return auxiliar.get_top();
}

//Função responsável por retornar o resultado final da expressão, utilizando sempre a notação posfixa para resolver
void Expression::solve(string value){
    Stack<node*> s;
    stringstream ss(value);
    string digit;
    //Caso a string esteja em posfixa, gera-se o resultado
    if(isPosfix(value)){
        while(ss >> digit){
        node* novo = new node(digit);
            //Cria uma árvore de forma a sempre ter 2 digitos como filho de um operador e insere na pilha de nós
            if (double_number(digit)){
                novo->data = digit;
                s.Empilha(novo);
            }else if(is_operator(digit.c_str()[0])){
                node* aux1 = s.Desempilha();
                node* aux2 = s.Desempilha();
                novo->data = digit;
                novo->left = aux2;
                novo->right = aux1;
                s.Empilha(novo);
            }
        }
        //O topo da pilha terá a árvore completa com a expressão
        node* head = s.get_top();
        //Utiliza a funcão recursion para resolver a árvore completa e retornar o resultado.
        cout << "VAL: " << recursion(head) << endl;
        head->destruct(head);
    //Caso a expressão esteja em notação infixa, será convertida e depois solucionada
    }else{
        string result = to_posfix(value);
        solve(result);
    }
}
    

//Destrutor da classe
void Expression::destruct(){
    while(!auxiliar.Vazia()){
        auxiliar.Desempilha();
    }
}

//Função recursiva para retornar o valor da expressão armazenada no nó passado como parâmetro
double Expression::recursion(node* s){
    //Caso seja uma folha, retorna o valor de ponto flutuante daquele digito
    if(s->right == nullptr && s->left == nullptr){
        return atof(s->data.c_str());
    //Caso seja um operador, efetua a respectiva operação com seus dois filhos
    }else{
        if(s->data == "+"){
            return recursion(s->left) + recursion(s->right);
        }
        if(s->data == "-"){
            return recursion(s->left) - recursion(s->right);
        }
        if(s->data == "*"){
            return recursion(s->left) * recursion(s->right);
        }
        if(s->data == "/"){
            if(recursion(s->right) == 0){
                zero_division error; 
                throw error;
            }
            return recursion(s->left) / recursion(s->right);
        }
    }
    return 0;
}

//Função responsável por converter a expressão armazenada para notação posfixa
string Expression::to_posfix(string op){
    Stack<string> operadores;
    string posfix = "";
    stringstream ss(op); 
    string digit;
    //Itera pela string que armazena a expressão
    while(ss >> digit){
        //Caso seja um numero, adiciona na string resultado o digito
        if(double_number(digit)){
            posfix += digit;
            posfix += " ";
        //Caso seja um parênteses de abertura, insere ele na pilha de operadores
        }else if(digit == "("){
            operadores.Empilha(digit);
        //Caso seja um parênteses de fechamento, insere o operador no topo, remove os elementos da pilha até encontrar o parêntes de abertura.
        }else if(digit == ")"){ 
            while(!operadores.Vazia() && operadores.get_top() != "("){
                posfix += operadores.get_top();
                operadores.Desempilha();
                posfix += " ";
            }
            //Desempilha o parênteses de abertura
            operadores.Desempilha();
        //Caso seja um operador, insere na string respeitando a precedencia de operadores da pilha enquanto não for encontrado
        // parênteses de abertura ou a pilha não esteja vazia
        }else if(is_operator(digit.c_str()[0])){ 
            while(!operadores.Vazia()  && operadores.get_top() != "(" && (precedence(operadores.get_top().c_str()[0])) >= precedence(digit.c_str()[0])){
                posfix += operadores.get_top();
                operadores.Desempilha();
                posfix += " ";
            }
        //Empilha o operador encontrado
        operadores.Empilha(digit);
        }
    }//Insere os ultimos operadores na string final
    while(!operadores.Vazia()){
        posfix += operadores.get_top();
        posfix += " ";
        operadores.Desempilha();
    }
    return posfix;
}
