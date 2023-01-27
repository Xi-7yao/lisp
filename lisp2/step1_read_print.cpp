#include "reader.cpp"
#include "printer.cpp"
#include <iostream>

Mal READ(String str){
    return read_str(str) ;
}

Mal EVAL(Mal m){
    return m ;
}

String PRINT(Mal m){
    return pr_str(m) ;    
}

String repl(String str){
    
    Mal t = EVAL(READ(str)) ;
    return pr_str(t) ;
}

int main()
{
    String str ;
    while(std::cout << "user>" , getline(std::cin , str)){
        std::cout << repl(str) << '\n' ;
    }
}