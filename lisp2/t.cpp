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
                    Mal tp ; tp.type = VECTOR_TYPE ; 
                    tp.vector_type.push_back(a->vector_type[1]) ; tp.vector_type.push_back(a->vector_type[2]) ;
                    if(!Equal(&tp).bool_type){
                        break ;
                    }
                    if(i == a->vector_type.size() - 1)  t.bool_type = true ;
                }
            }
        }
    }
    return t ;
}