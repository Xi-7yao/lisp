#include "type.h"
#include <iostream>

String READ(String str){
    return str ;
}

String EVAL(String str){
    return str ;
}

String PRINT(String str){
    return str ;
}

String repl(String str){
    return PRINT(EVAL(READ(str))) ;
}


int main()
{
    String str ;
    while(std::cin >> str){
        repl(str) ;
    }
}