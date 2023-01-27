#ifndef ENV_H
#define ENV_H

#include "type.h"

class Env{
    public :
        VectorStirng Fun_stock ;
        Map_String_Fun Sys_oper ;
        Map_String_Fun1 Sys_oper1 ;

        VectorStirng stock ;
        Map_String_Mal Map ;
        
        Map_String_Fun Fun_insert(String str , Fun function) ;
        Map_String_Fun1 Fun_insert1(String str , Fun1 function) ;
        void Set(String str , Mal m) ;
        Env* Find(String str , Env *env) ;
        Env* Find_Fun(String str , Env *env) ;
        Mal get(String str) ;
        Env(Mal a , Mal b) ; 
        Env() ;
        Env* last = NULL ;
    private :
};
bool is_VectorString(String a , VectorStirng b) ;
Mal Fun_emphasis(Mal *a , Mal *b , bool is_new) ;
Mal Set_list(Mal *m , int begin , int end) ;
Mal Set_list(Mal *m) ;
Mal Assigned(Mal *a , Mal *b , bool is_new) ;
bool Exit_Parameter(Mal *a) ;
void insert_function_name(Mal *a) ;


void insert_function_name(Mal *a , String name){
    a->function_name = name ;
    if(a->type == FUNCTION || a->type == VECTOR_TYPE){
        for(int i = 0 ; i < a->vector_type.size() ; i ++){
            insert_function_name(&a->vector_type[i] , name) ;
        }
    }
}
bool Exit_Parameter(Mal *a){
    if(a->type == FUNCTION){
        for(int i = 0 ; i < a->vector_type.size() ; i ++){
            if(a->vector_type[i].type == VECTOR_TYPE){
                return Exit_Parameter(&a->vector_type[i]) ;
            }
            else if(a->vector_type[i].type == PARAMETER)
                return true ;
        }
        return false ;
    }
    return false ;
}
Mal Fun_emphasis(Mal *a , Mal *b , bool is_new){
    if(is_new){
        for(int i = 0 ; i < b->vector_type.size() ; i ++){
            if(b->vector_type[i].parameter != -1)
                b->vector_type[i].parameter += a->vector_type.size() ;
        }
    }
    for(int i = 0 ; i < a->vector_type.size() ; i ++){
        String s = a->vector_type[i].string_type ;
        for(int j = 0 ; j < b->vector_type.size() ; j ++){
            if(b->vector_type[j].type == VECTOR_TYPE){
                Fun_emphasis(a , &b->vector_type[j] , false) ;
            }
            else  if(b->vector_type[j].string_type == s && b->vector_type[j].type != PARAMETER){
                b->vector_type[j].type = PARAMETER ;
                b->vector_type[j].parameter = i ;
            }
        }
    }
    if(is_new)
        b->type = FUNCTION ;
    else
        b->type = VECTOR_TYPE ;
    return *b ;
}
Mal Assigned(Mal *a , Mal *b , bool is_new){
    for(int i = 0 ; i < a->vector_type.size() ; i ++){
        for(int j = 0 ; j < b->vector_type.size() ; j ++){
            if(b->vector_type[j].type == VECTOR_TYPE){
                Assigned(a , &b->vector_type[j] , false) ;
            }
            else if(b->vector_type[j].parameter == i){
                b->vector_type[j] = a->vector_type[i] ;
            }
        }
    }
    if(is_new){
        for(int i = 0 ; i < b->vector_type.size() ; i ++){
            b->vector_type[i].parameter -= a->vector_type.size() ;
        }
    }
    if(!Exit_Parameter(b)){b->type = VECTOR_TYPE ;}
    return *b ;
}
Map_String_Fun1 Env::Fun_insert1(String str , Fun1 function){
    this->Sys_oper1.insert({str , function}) ;
    return this->Sys_oper1 ;
}
Env::Env(){}
Mal Set_list(Mal *m , int begin , int end){
    Mal t ; t.type = VECTOR_TYPE ;
    if(begin <= end){
        for(int i = begin ; i <= end ; i ++){
            t.vector_type.push_back(m->vector_type[i]) ;
        }
    }
    return t ;
}
Mal Set_list(Mal *m){
    Mal t ; t.type = VECTOR_TYPE ;
    t.vector_type.push_back(*m) ;
    return t ;
}
Env::Env(Mal a , Mal b){
    for(int i = 0 ; i < a.vector_type.size() ; i ++){
        this->Set(a.vector_type[i].string_type , b.vector_type[i]) ;
    }
}
Env* Env::Find_Fun(String str , Env *env){
    if(is_VectorString(str , env->Fun_stock))   return env ;
    else if(env->last != NULL)  return Find_Fun(str , env->last) ;
    else    return NULL ;
}
void Env::Set(String str , Mal m){
    if(!is_VectorString(str , this->stock)){ 
        this->stock.push_back(str) ;
        this->Map.insert({str , m}) ;
    }
    else{
        this->Map[str] = m ;
    }
}
Env* Env::Find(String str , Env *env){
    if(is_VectorString(str , env->stock))  return env ;
    else if(env->last != NULL)  return Find(str , env->last) ;
    else    return  NULL ;
}
Mal Env::get(String str){
    Env *t = Find(str , this) ;
    return t->Map[str] ;
}
bool is_VectorString(String a , VectorStirng b){
    for(int i = 0 ; i < b.size() ; i ++){
        if(a == b[i])   return true ;
    }
    return false ;
}
// Mal add(Mal a , Mal b){
//     Mal t ; t.type = NUM_TYPE ;
//     t.num_type = a.num_type + b.num_type ;
//     return t ; 
// }
// Mal sub(Mal a , Mal b){
//     Mal t ; t.type = NUM_TYPE ;
//     t.num_type = a.num_type - b.num_type ;
//     return t ; 
// }
// Mal mult(Mal a , Mal b){
//     Mal t ; t.type = NUM_TYPE ;
//     t.num_type = a.num_type * b.num_type ;
//     return t ; 
// }
// Mal div(Mal a , Mal b){
//     Mal t ; t.type = NUM_TYPE ;
//     t.num_type = a.num_type / b.num_type ;
//     return t ; 
// }
Map_String_Fun Env::Fun_insert(String str , Fun function){
    this->Sys_oper.insert({str , function}) ;
    return this->Sys_oper ;
}

#endif