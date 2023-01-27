#include "reader.cpp"
#include "printer.cpp"
#include <iostream>
#include "env.h"

Mal READ(String str) ;
Mal EVAL(Mal m , Env *env) ;
String PRINT(Mal m) ;
String repl(String str , Env *env) ;
Mal eval_ast(Mal m , Env *env) ;


Mal READ(String str){
    return read_str(str) ;
}
Mal EVAL(Mal m , Env *env){
    if(m.type == VECTOR_TYPE){
        if(m.vector_type.empty()){
            return m ;
        }
        else{
            Mal t = eval_ast(m , env) ;
            // for(int i = 0 ; i < t.vector_type.size() ; i ++){
            //     std::cout << t.vector_type[i].num_type << " " ;
            // }
            // std::cout << ' ' ;
            Fun function = env->Sys_oper[t.vector_type[0].string_type] ;
            Mal tp = function(t.vector_type[1] , t.vector_type[2]) ;
            // std::cout << tp.num_type << '\n' ;   
            return tp ;
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
    Mal t = EVAL(READ(str) , env) ;
    return PRINT(t) ;
}
Mal eval_ast(Mal m , Env *env){
    if(m.type == VECTOR_TYPE){
        Mal list ; list.type = VECTOR_TYPE ;
        for(int i = 0 ; i < m.vector_type.size() ; i ++){
            list.vector_type.emplace_back(EVAL(m.vector_type[i] , env)) ;
        }
        return list ;
    }
    else if(m.type == STRING_TYPE && is_VectorString(m.string_type , env->stock)){
        return env->Map[m.string_type] ;
    }
    return m ;
}

int main()
{
    String str ;
    Env env ;
    env.Map_insert("+" , add); 
    env.Map_insert("-" , sub); 
    env.Map_insert("*" , mult);
    env.Map_insert("/" , div); 

    while(std::cout << "user>" , getline(std::cin , str)){
        std::cout << repl(str , &env) << '\n' ;
    }
}