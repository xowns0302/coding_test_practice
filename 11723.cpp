#include <iostream>
#include <set>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int M;
    cin>>M;
    set <int> S;
    for(int i=0;i<M;i++){
        string str;
        cin>>str;
        int a;
        if(str =="add"){
            cin>>a;
            S.insert(a);
        }
        else if(str=="remove"){
            cin>>a;
            S.erase(a);
        }
        else if(str=="check"){
            cin>>a;
            cout<<S.count(a)<<"\n";
        }
        else if(str=="toggle"){
            cin>>a;
            if(S.count(a)){
                S.erase(a);
            }else{
                S.insert(a);
            }
        }
        else if(str=="all"){
            S={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
        }
        else if(str=="empty"){
            S.clear();
        }
    }
}