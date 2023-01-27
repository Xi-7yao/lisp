#include "reader_second.cpp"
#include "printer.cpp"
#include "core.cpp"
#include <iostream>
#include "env.h"

Mal READ(String str) ;
Mal EVAL(Mal m , Env *env) ;
String PRINT(Mal m) ;
String repl(String str , Env *env) ;
Mal eval_ast(Mal m , Env *env) ;


int main()
{
    String str ;
    Env env ;
    env.Fun_insert1("+" , add) ; env.Fun_stock.push_back("+") ;
    env.Fun_insert1("-" , sub) ; env.Fun_stock.push_back("-") ;
    env.Fun_insert1("*" , mult) ; env.Fun_stock.push_back("*") ;
    env.Fun_insert1("/" , div) ; env.Fun_stock.push_back("/") ;
    env.Fun_insert1("prn" , prn) ; env.Fun_stock.push_back("prn") ;
    env.Fun_insert1("list?" , is_list) ; env.Fun_stock.push_back("list?") ;
    env.Fun_insert1("empty?" , is_empty) ; env.Fun_stock.push_back("empty?") ;
    env.Fun_insert1("count" , count) ; env.Fun_stock.push_back("count") ;
    env.Fun_insert1("=" , Equal) ; env.Fun_stock.push_back("=") ;
    env.Fun_insert1("<" , less) ; env.Fun_stock.push_back("<") ;
    env.Fun_insert1("<=" , less_equal) ; env.Fun_stock.push_back("<=") ;
    env.Fun_insert1(">" , greater) ; env.Fun_stock.push_back(">") ;
    env.Fun_insert1(">=" , greater_equal) ; env.Fun_stock.push_back(">=") ;
    

    while(std::cout << "user>" , getline(std::cin , str)){
        if(str == "") continue ;
        std::cout << repl(str , &env) << '\n' ;
    }
}


Mal READ(String str){
    return read_str(str) ;
}
Mal EVAL(Mal m , Env *env){
    if(m.type == VECTOR_TYPE || m.type == FUNCTION){
        if(m.vector_type.empty()){
            return m ;
        }
        else{
            Mal t = eval_ast(m , env) ;
            Env *env1 = env->Find_Fun(t.vector_type[0].string_type , env) ;
            
            if(t.vector_type[0].string_type == "fn*"){
                Mal third ;
                if(t.vector_type[2].type == VECTOR_TYPE || t.vector_type[2].type == FUNCTION)    third = t.vector_type[2] ;
                else    third = Set_list(&t.vector_type[2]) ;
                Mal p = Fun_emphasis(&t.vector_type[1] , &third , true)  ;
                return p ;
            }
            else if(t.vector_type[0].string_type == "list"){
                return list(&t) ;
            }
            else if(t.vector_type[0].string_type == "def!"){
                Mal tmp = t.vector_type[2] ;
                env->Set(t.vector_type[1].string_type , tmp) ;
                return tmp ;
            }
            else if(t.vector_type[0].string_type == "do"){
                return t.vector_type[t.vector_type.size() - 1] ;
            }
            else if(t.vector_type[0].string_type == "if"){
                if(t.vector_type[1].type == BOOL_TYPE){
                    if(t.vector_type[1].bool_type){
                        return t.vector_type[2] ;
                    }
                    else{
                        return t.vector_type[3] ;
                    }
                }
            }
            else if(t.vector_type[0].string_type == "let*"){
                Mal tmp = t.vector_type[1] ;
                Mal temp = t.vector_type[2] ;
                Env env2 ;  
                env2.last = env ;
                for(int i = 0 ; i < tmp.vector_type.size() / 2 ; i ++){
                    Mal T = EVAL(tmp.vector_type[2 * i + 1] , &env2) ;
                    env2.Set(tmp.vector_type[2 * i].string_type , T) ;
                }
                return env2.get(temp.string_type) ;
            }
            else if(env1 != NULL){    
                Fun1 function = env1->Sys_oper1[t.vector_type[0].string_type] ;
                return function(&t) ;
            }
            else if(t.vector_type[0].type == FUNCTION){
                Mal tp = eval_ast(Set_list(&t , 1 , t.vector_type.size() - 1) , env) ;
                Mal T = Assigned(&tp , &t.vector_type[0] , true) ;
                T = EVAL(T , env) ;
                if(T.type == VECTOR_TYPE && T.vector_type.size() == 1)   return T.vector_type[0] ;
                insert_function_name(&T , "") ;
                return EVAL(T , env) ;
            }
            return t ;
        }
    }
    else{
        return eval_ast(m , env) ;
    }
    return m ;
}
String PRINT(Mal m){
    return pr_str(m) ;
}
String repl(String str , Env *env){
    Mal tp = READ(str) ;
    Mal t = EVAL(READ(str) , env) ;
    return PRINT(t) ;
}
Mal eval_ast(Mal m , Env *env){
    if(m.type == VECTOR_TYPE){
        Mal list ; list.type = VECTOR_TYPE ;
        list.function_name = m.function_name ;
        for(int i = 0 ; i < m.vector_type.size() ; i ++){
            list.vector_type.push_back(EVAL(m.vector_type[i] , env)) ;
        }
        return list ;
    }
    else if(m.type == STRING_TYPE && is_VectorString(m.string_type , env->stock)){
        Mal t = env->get(m.string_type) ;
        if(t.type == FUNCTION){
            if(m.function_name == m.string_type)
                return m ;
            for(int i = 0 ; i < t.vector_type.size() ; i ++)
                insert_function_name(&t.vector_type[i] , m.string_type) ;
        }
        return t ;
    }
    return m ;
}
