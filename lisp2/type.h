#ifndef TYPE_H
#define TYPE_H

#include <string> 
#include <vector>
#include <unordered_map>

#define NUM_TYPE 0
#define STRING_TYPE 1
// #define SYSBOL_TYPE 2
#define VECTOR_TYPE 3
#define BOOL_TYPE 4
#define KEYWORD_TYPE 5
#define HASH_TYPE 6
#define PARAMETER 8
#define FUNCTION 9 

typedef std::string             String;
typedef std::vector<String>     VectorStirng ;

struct Mal
{
    int type = -1 ;
    double num_type = 0 ;
    String string_type = "" ;
    // String sysbol_type = "" ;
    std::vector<Mal> vector_type ;
    bool bool_type = false ;
    int parameter = -1 ;
    // String keyword_type = "" ;
    String function_name = "" ;
};

typedef std::vector<Mal>        VectorMAL ;
typedef Mal                     (*Fun)(Mal , Mal) ;
typedef Mal                     (*Fun1)(Mal*) ;
typedef std::unordered_map<String , Mal> Map_String_Mal ;
typedef std::unordered_map<String , Fun>  Map_String_Fun ;
typedef std::unordered_map<String , Fun1>  Map_String_Fun1 ;

#endif