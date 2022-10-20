#include <bits/stdc++.h>
using namespace std;

string READ()
{
    string res ; getline(cin , res) ;
    return res ;
}

string EVAL(string str)
{
    return str ;
}

string PRINT(string str)
{
    return str ;
}

int main()
{
    while(true){
        cout << "user>" ;
        string str = READ() ;
        str = EVAL(str) ;
        str = PRINT(str) ;
        cout << str << '\n' ;
    }
}