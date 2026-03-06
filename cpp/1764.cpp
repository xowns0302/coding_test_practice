#include <iostream>
#include <set>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int N,M;
    int c=0;
    cin>>N>>M;
    set <string>L,S,R;
    for(int i=0;i<N;i++){
        string str;
        cin>>str;
        L.insert(str);
    }
    for(int i=0;i<M;i++){
        string str;
        cin>>str;
        S.insert(str);
        if(L.count(str)){
            c+=L.count(str);
            R.insert(str);
        }
    }
    cout<<c<<"\n";
    for(const auto &s: R){
        cout<<s<<"\n";
    }
    return 0;
}