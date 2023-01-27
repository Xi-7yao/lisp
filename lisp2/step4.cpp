#include "reader.cpp"
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
    env.Fun_insert("+" , add) ; env.Fun_stock.push_back("+") ;
    env.Fun_insert("-" , sub) ; env.Fun_stock.push_back("-") ;
    env.Fun_insert("*" , mult) ; env.Fun_stock.push_back("*") ;
    env.Fun_insert("/" , div) ; env.Fun_stock.push_back("/") ;
    env.Fun_insert1("prn" , prn) ; env.Fun_stock.push_back("prn") ;
    env.Fun_insert1("list?" , is_list) ; env.Fun_stock.push_back("list?") ;
    env.Fun_insert1("empty?" , is_empty) ; env.Fun_stock.push_back("empty?") ;
    env.Fun_insert1("count" , count) ; env.Fun_stock.push_back("count") ;
    // env.Fun_insert("=" , equal) ; env.Fun_stock.push_back("=") ;
    env.Fun_insert("<" , less) ; env.Fun_stock.push_back("<") ;
    env.Fun_insert("<=" , less_equal) ; env.Fun_stock.push_back("<=") ;
    env.Fun_insert(">" , greater) ; env.Fun_stock.push_back(">") ;
    env.Fun_insert(">=" , greater_equal) ; env.Fun_stock.push_back(">=") ;
    

    while(std::cout << "user>" , getline(std::cin , str)){
        std::cout << repl(str , &env) << '\n' ;
    }
}


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
            // print_Mal(t) ;
            // std::cout << '\n' ;
            int len = t.vector_type.size() ;

            // for(int i = 0 ; i < t.vector_type.size() ; i ++){
            //     print_Mal(t.vector_type[i]) ;
            // }

            String tp = t.vector_type[0].string_type ;
            Env *env1 = env->Find_Fun(t.vector_type[0].string_type , env) ;
            int fn_place = Find_fn(t) ;
            int list_place = Find_list(t) ;

            if(list_place != -1){
                return Set_list(t , 1 , t.vector_type.size() - 1) ;
            }
            if(fn_place != -1){
                int fn_len = t.vector_type[fn_place].vector_type[1].vector_type.size() ;
                Mal TP = eval_ast(Set_list(t , fn_place + 1 , fn_place + fn_len) , env) ;
                // print_Mal(TP) ;
                Env env2(t.vector_type[fn_place].vector_type[1] , eval_ast(Set_list(t , fn_place + 1 , fn_place + fn_len) , env)) ;
                env2.last = env ;
                return EVAL(t.vector_type[fn_place].vector_type[2] , &env2) ;
            }
            if(tp == "def!"){
                Mal tmp = EVAL(t.vector_type[2] , env) ;
                env->Set(t.vector_type[1].string_type , tmp) ;
                return tmp ;
            }
            else if(tp == "do"){
                return t.vector_type[len - 1] ;
            }
            else if(tp == "if"){
                if(t.vector_type[1].bool_type){
                    return t.vector_type[2] ;
                }
                else{
                    return t.vector_type[3] ;
                }
            }
            else if(tp == "let*"){
                Mal tmp = t.vector_type[1] ;
                Mal temp = t.vector_type[2] ;
                Env env1 ;  
                env1.last = env ;
                for(int i = 0 ; i < tmp.vector_type.size() / 2 ; i ++){
                    Mal T = EVAL(tmp.vector_type[2 * i + 1] , &env1) ;
                    env1.Set(tmp.vector_type[2 * i].string_type , T) ;
                }
                return env1.get(temp.string_type) ;
            }
            else if(env1 != NULL){    
                if(len == 2){
                    Fun1 function = env1->Sys_oper1[t.vector_type[0].string_type] ;
                    return function(t.vector_type[1]) ;
                }
                if(len == 3){
                    Fun function = env1->Sys_oper[t.vector_type[0].string_type] ;
                    return function(t.vector_type[1] , t.vector_type[2]) ;
                }
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
    Mal t = EVAL(READ(str) , env) ;
    return PRINT(t) ;
}
Mal eval_ast(Mal m , Env *env){
    if(m.type == VECTOR_TYPE){
        Mal list ; list.type = VECTOR_TYPE ;
        for(int i = 0 ; i < m.vector_type.size() ; i ++){
            list.vector_type.push_back(EVAL(m.vector_type[i] , env)) ;
        }
        return list ;
    }
    else if(m.type == STRING_TYPE && is_VectorString(m.string_type , env->stock)){
        return env->get(m.string_type) ;
    }
    return m ;
}
