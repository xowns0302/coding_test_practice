#include <iostream>
#include <vector>
using namespace std;

int t,res=0;
string arr;
vector <vector<int>>trie;
vector <int>fin;
int sz=1;

void ins(){
    int cur=0;
    for(int i=0; arr[i];++i){
        int nxt=arr[i];
        if(!trie[cur][nxt])trie[cur][nxt]=sz++;
        cur=trie[cur][nxt];
    }
    fin[cur]=1;
}

int query(){
    int cur = 0;
    for (int i = 0; arr[i]; ++i) {
        int nxt = arr[i] -'a';
        if(!trie[cur][nxt]) return 0;
    }
    return 0;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>t;
    for(int i=0;i<t;i++){
        int n;
        cin>>n;
        for(int j=0;j<n;j++){
            cin>>arr;
            ins();
            res+=query();
        }
    }
    return 0;
}