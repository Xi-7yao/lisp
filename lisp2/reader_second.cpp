#include "Regex.h"
#include "type.h"
// #include "printer.cpp"               //仅测试时使用
#include <iostream>

class Reader{
    private :
        VectorStirng tokens ;
        int position = 0 ;
    public :
        Reader(VectorStirng a) ;
        String next();
        String peek() ;
};

int StringToNum(String str , int ind) ;
Mal read_atom(String str) ;
Mal read_list(Reader &r) ;
Mal read_str(String str) ;
Mal read_form(Reader &r) ;

String Reader::next(){
    return tokens[position ++] ;
}
String Reader::peek(){
    return tokens[position] ;
}
Reader::Reader(VectorStirng a){
    this->tokens = a ;
}

VectorStirng tokenize(String str){
    VectorStirng list ;
    String t = "[\\s,]*(~@|[\\[\\]{}()'`~^@]|\"(?:\\\\.|[^\\\"])*\"?|;.*|[^\\s\\[\\]{}('\"`,;)]*)" ;
    Regex r(t) ;
    Smatch result ;
    int q = 0 , len = str.size() ;
    while(q < len){
        if(regex_search(str , result , r)){
            list.push_back(result.str(1)) ;
            q += result.length() ;
            str = result.suffix() ;
        }
        else
            break ;
    }
    // for(int i = 0 ; i < list.size() ; i ++){
    //     std::cout << list[i] << " " ;
    // }
    return list ;
}

bool Char_is_String(char a , String b){
    for(int i = 0 ; i < b.size() ; i ++)
        if(a == b[i])   return true ;
    return false ;
}

int StringToNum(String str , int ind){
    int res = 0 ;
    for(int i = ind ; i < str.size() ; i ++){
        res = res * 10 + str[i] - '0' ;
    }
    return res ;
}

Mal read_atom(String str){
    Mal t ;
    if(str[0] == '-' && str.size() > 1){
        t.type = NUM_TYPE ;
        t.num_type = StringToNum(str , 1) * -1 ;
    }
    // else if(str.size() == 1 && is_exit(str[0] , Oper)){
    //     t.type = SYSBOL_TYPE ;
    //     t.sysbol_type = str[0] ;
    // }
    else if(str[0] >= '0' && str[0] <= '9'){
        t.type = NUM_TYPE ;
        t.num_type = StringToNum(str , 0) ;
    }
    else if(str == "true" || str == "True" || str == "TRUE"){
        t.type = BOOL_TYPE ;
        t.bool_type = true ;
    }
    else if(str == "false" || str == "False" || str == "FALSE"){
        t.type = BOOL_TYPE ;
        t.bool_type = false ;
    }
    else{
        t.type = STRING_TYPE ;
        t.string_type  = str ;
    }
    return t ; 
}

Mal read_form(Reader &r){
    String token = r.next() ;
    if(token == "(" || token == "["){
        return read_list(r) ;
    }
    else{
        return read_atom(token) ;
    }
}

Mal read_list(Reader &r){
    Mal t ; t.type = VECTOR_TYPE ;
    while(true){
        if(r.peek() == ")" || r.peek() == "]"){
            r.next() ;  
            break ; 
        }
        Mal tp = read_form(r) ;
        // tp.father = &t ;
        t.vector_type.push_back(tp) ;
    }
    return t ;
}

Mal read_str(String str){
    Reader r(tokenize(str)) ;
    // while(r.peek() != ""){
    //     std::cout << r.next() ;
    // }
    Mal t = read_form(r) ;
    // std::cout << pr_str(t) ;
    return t ;
}

// int main()
// {
//     String str ; 
//     getline(std::cin , str) ;
//     Mal t = read_str(str) ;
//     print_Mal(t) ;
// } 