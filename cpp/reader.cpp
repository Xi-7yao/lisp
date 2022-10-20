#include <bits/stdc++.h>
using namespace std;

union Mal
{
    int num ;
    char sym ;
};

class Reader
{
    public:
        Reader(vector<string> a , int b)
        {
            s = a ;
            pos = b ;
        }
        string next()
        {
            return s[pos ++] ;
        }
        string peek()
        {
            return s[pos] ;
        }
    private:
        vector<string> s ;
        int pos = -1 ;
};

vector<string> tokenize(string str)
{
    vector<string> res ;
    //      [\s,]*(~@|[\[\]{}()'`~^@]|"(?:\\.|[^\\"])*"?|;.*|[^\s\[\]{}('"`,;)]*)
    string t = "[\\s,]*(~@|[\\[\\]\\{\\}\\(\\)'`~^@]|\"?:\\\\.\\|[^\\\\]\")" ;
    cout << t << '\n' ;
    // regex R(t) ;
    return res ;
}

void read_str(string str)
{
    vector<string> t = tokenize(str) ;
    Reader r(t , t.size() - 1) ;
}

Mal read_form(Reader r)
{
    string t = r.peek() ;
    // if(t[0] == '(')         return read_list(r) ;
    // else                    return read_atom(r) ;
    Mal a ;
    return a ;
}

Mal read_atom(string str)
{
    Mal t ;
    if(str[0] >= '0' && str[0] <= '9'){
        int res = 0 ;
        for(int i = 0 ; i < str.size() ; i ++)
            res = res * 10 + str[i] - '0' ;
        t.num = res ;
    }
    else{
        t.sym = str[0] ;
    }
    return t ;
}

Mal read_list(Reader r)
{
    Mal a ;
    return a ;
}

int main()
{
    // cout << "[\\s,]*(~@|[\\[\\]{}'`~^@]|\"(?:\\\\.|[^\\\\\"])*\")*\"?|;.*|[^\\s\\[\\]{}('\"`,;)]*" << '\n' ;
    string str ; getline(cin , str) ;
    // cout << str << '\n' ;
    vector<string> a = tokenize(str) ;
    for(int i = 0 ; i < a.size() ; i ++)
        cout << a[i] << '\n' ;
}