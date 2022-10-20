#include <bits/stdc++.h>
using namespace std;

int main()
{
    string a = "bbc1acbc1adv" ;
    cout << a << '\n' ;
    string t = "a([a-z]*)" ;
    cout << t << '\n' ;
    regex R(t) ;
    smatch result ;
    if(regex_match(a , result , R)){
        for(auto &x : result){
            cout << x << "\n" ;
        }
    }
}