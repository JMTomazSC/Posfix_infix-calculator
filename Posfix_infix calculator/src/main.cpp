#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/time.h>
#include <sys/resource.h>
#include "../include/Expression.hpp"

#define MAXTAM 100

using namespace std;

int main(){
//Código propicio para fazer a analise experimental de eficiência do código
struct timespec clock_start, clock_end;
struct rusage start, end;
double T_sys, T_user, T_clock; 
getrusage(RUSAGE_SELF, &start);
clock_gettime(CLOCK_MONOTONIC, &clock_start);

cout << fixed << setprecision(6); //Fazendo com que a precisão do código seja de até 6 casas decimais.
//Pode existir pequenos erros númericos devido ao setprecision
string line;
string operation;
string valid = "";
string result;
//Iterando pelas strings do arquivo dividindo-as por um \n
    while(getline(cin,line,'\n')){
        Expression s = Expression();
        // Caso a substring ler esteja no inicio do arquivo, executa a função para efetuar a leitura.
        if(line.substr(0,10) == "LER INFIXA"){
            operation = line.substr(11,line.length() - 11);
            try{
            s.read_infix_expression(operation);
            //Caso a expressão passe pelos requisitos de uma expressão válida e nenhuma excessão seja retirada
            //Armazena-se a string válida
            valid += operation;
            }catch(not_valid_expression error){
                cout << "ERRO: " << operation << "NAO VALIDA" << endl;
            }
        //Caso a substring INFIXA esteja no inicio, executa a função de conversão para infixa    
        }else if(line.substr(0,11) == "LER POSFIXA"){
            operation = line.substr(12,line.length() - 12);
            try{
            s.read_posfix_expression(operation);
            //Caso a expressão passe pelos requisitos de uma expressão válida e nenhuma excessão seja retirada
            //Armazena-se a string válida
            valid += operation;
            }catch(not_valid_expression error){
                cout << "ERRO: " << operation << "NAO VALIDA" << endl;
            }
        }else if(line.substr(0,6) == "INFIXA"){
            try{
                 //Caso a expressão não tenha sido armazenada, retorna uma excessão
                if(valid == ""){
                    not_exist_expression error;
                    error.expression = operation;
                    throw error;
                }
                if(!s.isPosfix(valid)){
                    cout << "INFIXA: " << valid << endl;
                }else{
                result = s.to_infix(operation);
                cout << "INFIXA: " << result << endl;
                }
            }catch(not_exist_expression error){
                cout << "ERRO: EXP NAO EXISTE" << endl;
            }
        //Caso a substring POSFIXA esteja no inicio, executa a função de conversão para posfixa
        }else if(line.substr(0,7) == "POSFIXA"){
            try{
                 //Caso a expressão não tenha sido armazenada, retorna uma excessão
                if(valid == ""){
                    not_exist_expression error;
                    error.expression = operation;
                    throw error;
                }
                if(s.isPosfix(valid)){
                    cout << "POSFIXA: " << valid << endl;
                }else{
                result = s.to_posfix(operation);
                cout << "POSFIXA: " << result << endl;
                }
            }catch(not_exist_expression error){
                cout << "ERRO: " << operation << "NAO EXISTE" << endl;
            }
        //Caso a substring RESOLVE esteja no inicio, executa a função que retornara o resultado da expressão   
        }else if(line.substr(0,7) == "RESOLVE"){
            try{
                //Caso a expressão não tenha sido armazenada, retorna uma excessão
                if(valid == ""){
                    not_exist_expression error;
                    error.expression = operation;
                    throw error;
                }
                s.solve(operation);
            }catch(not_exist_expression error){
                cout << "ERRO: EXP NAO EXISTE" << endl;
            }catch(zero_division error){
                cout << "ERRO: DIVISÃO POR ZERO" << endl;
            }
        }else{

        }
    }      
    getrusage(RUSAGE_SELF, &end);
    clock_gettime(CLOCK_MONOTONIC, &clock_end);

    //Calcula os tempos necessários
    T_clock = (clock_end.tv_sec - clock_start.tv_sec) + (clock_end.tv_nsec - clock_start.tv_nsec)/10e9;
    T_sys = (end.ru_stime.tv_sec - start.ru_stime.tv_sec) + (end.ru_stime.tv_usec - start.ru_stime.tv_usec)/10e6;
    T_user = (end.ru_utime.tv_sec - start.ru_utime.tv_sec) + (end.ru_utime.tv_usec - start.ru_utime.tv_usec)/10e6;

    T_clock /= 8;
    T_clock *= 1000;

    cout << "Tempo de sistema: " << T_sys << endl << "Tempo de usuario: " << T_user << endl << "Tempo de relogio: " << T_clock << endl;

return 0;
}