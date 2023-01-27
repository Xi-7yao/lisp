#include "type.h"
// #include "printer.cpp"
#include "env.h"

Map_String_Fun core ;

bool All_Is_NUM_TYPE(Mal *a){
    for(int i = 1 ; i < a->vector_type.size() ; i ++){
        if(a->vector_type[i].type != NUM_TYPE)
            return false ;
    }
    return true ;
}

Mal add(Mal *a){
    if(All_Is_NUM_TYPE(a)){
        Mal t ; t.type = NUM_TYPE ;
        t.num_type = a->vector_type[1].num_type ;
        for(int i = 2 ; i < a->vector_type.size() ; i ++){
            t.num_type += a->vector_type[i].num_type ;
        }
        return t ;
    }
    else{
        return *a ;
    }
}
Mal sub(Mal *a){
    if(All_Is_NUM_TYPE(a)){
        Mal t ; t.type = NUM_TYPE ;
        t.num_type = a->vector_type[1].num_type ;
        for(int i = 2 ; i < a->vector_type.size() ; i ++){
            t.num_type -= a->vector_type[i].num_type ;
        }
        return t ;
    }
    else{
        return *a ;
    }
}
Mal mult(Mal *a){
    if(All_Is_NUM_TYPE(a)){
        Mal t ; t.type = NUM_TYPE ;
        t.num_type = a->vector_type[1].num_type ;
        for(int i = 2 ; i < a->vector_type.size() ; i ++){
            t.num_type *= a->vector_type[i].num_type ;
        }
        return t ;
    }
    else{
        return *a ;
    }
}
Mal div(Mal *a){
    if(All_Is_NUM_TYPE(a)){
        Mal t ; t.type = NUM_TYPE ;
        t.num_type = a->vector_type[1].num_type ;
        for(int i = 2 ; i < a->vector_type.size() ; i ++){
            t.num_type /= a->vector_type[i].num_type ;
        }
        return t ;
    }
    else{
        return *a ;
    }
}
Mal prn(Mal *m){
    print_Mal(&m->vector_type[1]) ; std::cout << '\n' ;
    Mal t ; t.type = STRING_TYPE ;
    t.string_type = "nil" ;
    return t ;
}
Mal list(Mal *m){
    return Set_list(m , 1 , m->vector_type.size() - 1) ;
}
Mal is_list(Mal *m){
    Mal t ; t.type = BOOL_TYPE ;
    if(m->vector_type[1].type == VECTOR_TYPE)   t.bool_type = true ;
    else t.bool_type = false ;
    return t ;
}
Mal is_empty(Mal *m){
    Mal t ; t.type = BOOL_TYPE ;
    if(m->vector_type[1].vector_type.empty())   t.bool_type = true ;
    else t.bool_type = false ;
    return t ;
}
Mal count(Mal *m){
    Mal t ; t.type = NUM_TYPE ;
    t.num_type = m->vector_type[1].vector_type.size() ;
    return t ;
}
Mal Equal(Mal *a){
    Mal t ; t.type = BOOL_TYPE ; t.bool_type = false ;
    if(a->vector_type[1].type == a->vector_type[2].type){
        if(a->vector_type[1].type == STRING_TYPE && a->vector_type[1].string_type == a->vector_type[2].string_type) 
            t.bool_type = true ;
        if(a->vector_type[1].type == NUM_TYPE && a->vector_type[1].num_type == a->vector_type[2].num_type)  
            t.bool_type = true ;
        if(a->vector_type[1].type == BOOL_TYPE && a->vector_type[1].bool_type == a->vector_type[2].bool_type)   
            t.bool_type = true ;
        if(a->vector_type[1].type == VECTOR_TYPE){
            if(a->vector_type[1].vector_type.size() == a->vector_type[2].vector_type.size()){
                for(int i = 0 ; i < a->vector_type[1].vector_type.size() ; i ++){
                    Mal tp ; tp.type = VECTOR_TYPE ; tp.vector_type.push_back(a->vector_type[0]) ;
                    tp.vector_type.push_back(a->vector_type[1].vector_type[i]) ; tp.vector_type.push_back(a->vector_type[2].vector_type[i]) ;
                    if(!Equal(&tp).bool_type){
                        break ;
                    }
                    if(i == a->vector_type[1].vector_type.size() - 1)  t.bool_type = true ;
                }
            }
        }
    }
    return t ;
}
Mal greater(Mal *a){
    if(a->vector_type[1].type == NUM_TYPE && a->vector_type[2].type == NUM_TYPE){
        Mal t ;t.type = BOOL_TYPE ;
        t.bool_type = a->vector_type[1].num_type > a->vector_type[2].num_type ;
        return t ;
    }
    return *a ;
}
Mal greater_equal(Mal *a){
    if(a->vector_type[1].type == NUM_TYPE && a->vector_type[2].type == NUM_TYPE){
        Mal t ; t.type = BOOL_TYPE ;
        t.bool_type = a->vector_type[1].num_type >= a->vector_type[2].num_type ;
        return t ;
    }
    return *a ;
}
Mal less(Mal *a){
    if(a->vector_type[1].type == NUM_TYPE && a->vector_type[2].type == NUM_TYPE){
        Mal t ; t.type = BOOL_TYPE ;
        t.bool_type = a->vector_type[1].num_type < a->vector_type[2].num_type ;
        return t ;
    }
    return *a ;
}
Mal less_equal(Mal *a){
    if(a->vector_type[1].type == NUM_TYPE && a->vector_type[2].type == NUM_TYPE){
        Mal t ; t.type = BOOL_TYPE ;
        t.bool_type = a->vector_type[1].num_type <= a->vector_type[2].num_type ;
        return t ;
    }
    return *a ;
}
int Find_list(Mal m){
    if(m.type == VECTOR_TYPE){
        for(int i = 0 ; i < m.vector_type.size() ; i ++){
            if(m.vector_type[i].string_type == "list")  
                return i ;
        }
    }
    return -1 ;
}