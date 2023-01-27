#include "type.h"
#include <iostream>

String pr_str(Mal m) ;
void print_Mal(Mal *m) ;

String pr_str(Mal m){
    if(m.type == FUNCTION){
        return "#<function>" ;
    }
    if(m.type == NUM_TYPE)
        return std::to_string(m.num_type) ;
    if(m.type == STRING_TYPE)
        return m.string_type ;
    if(m.type == VECTOR_TYPE){
        String res ;
        res += "(" ; 
        for(int i = 0 ; i < m.vector_type.size() ; i ++){
            res += pr_str(m.vector_type[i]) ;
            if(i != m.vector_type.size() - 1) res += " " ;
        }
        res += ")" ;
        return res ;
    }
    if(m.type == BOOL_TYPE){
        if(m.bool_type) return "true" ;
        return "false" ;
    }
    return "" ;
}

void print_Mal(Mal *m){
    if(m->type == NUM_TYPE)  std::cout << m->num_type ;
    else if(m->type == STRING_TYPE)  std::cout << m->string_type ;
    else if(m->type == VECTOR_TYPE){
        for(int i = 0 ; i < m->vector_type.size() ; i ++){
            print_Mal(&m->vector_type[i]) ;
            std::cout << " " ;
        }
    }
    else if(m->type == FUNCTION){
        std::cout << "#<function> " ;
    }
    else if(m->type == BOOL_TYPE){
        if(m->bool_type)    std::cout << "true" ;
        else std::cout << "no" ;
    }
}