Mal greater(Mal *a){
    Mal t ; t.type = BOOL_TYPE ;
    t.bool_type = a->vector_type[1].num_type > a->vector_type[2].num_type ;
    return t ;
}
Mal greater_equal(Mal *a){
    Mal t ; t.type = BOOL_TYPE ;
    t.bool_type = a->vector_type[1].num_type >= a->vector_type[2].num_type ;
    return t ;
}
Mal less(Mal *a){
    Mal t ; t.type = BOOL_TYPE ;
    t.bool_type = a->vector_type[1].num_type < a->vector_type[2].num_type ;
    return t ;
}
Mal less_equal(Mal *a){
    Mal t ; t.type = BOOL_TYPE ;
    t.bool_type = a->vector_type[1].num_type <= a->vector_type[2].num_type ;
    return t ;
}