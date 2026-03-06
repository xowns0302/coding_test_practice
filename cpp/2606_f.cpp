/**이건 #2606번 보완버전
 * 재귀함수를 사용했음 거의 비슷한데 이게더 코드가 깔끔함
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <vector <int>>g;
vector <bool>v;
int c=0;

void dfs(int node){
    v[node]=true;

    for(int next : g[node]){
        if(!v[next]){
            c++;
            dfs(next);
        }
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int N,M;
    cin>>N>>M;
    
    g.resize(N+1);
    v.resize(N+1,false);

    for(int i=0;i<M;i++){
        int a,b;
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(1);

    cout<<c;
    return 0;
}
