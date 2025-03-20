//trie
#include <iostream>

using namespace std;

int N,M,res;
string str;
int trie[5050505][26], fin[5050505],sz=1;

void ins(){
    int cur=0;
    for(int i=0; str[i];++i){
        int nxt=str[i]-'a';
        if(!trie[cur][nxt]) trie[cur][nxt]=sz++;
        cur=trie[cur][nxt];
    }
    fin[cur]=1;
}

int query() {
    int cur = 0;
    for (int i = 0; str[i]; ++i) {
        int nxt = str[i] -'a';
        if(!trie[cur][nxt]) return 0;
        cur = trie[cur][nxt];
    }
    return fin[cur];
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;
    for(int i=0;i<N;i++){
        cin>>str;
        ins();
    }
    for(int i=0; i<M;i++){
        cin>>str;
        res+=query();
    }
    cout<<res<<"\n";
    return 0;

}