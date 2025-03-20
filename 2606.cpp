#include <iostream>
#include <vector>
/*이문제는 기초 탐색 문제인듯
먼저 2차원 배열로 각 노드가 연결된 녀석들을 
표현해줬음 예제 문제로 보면
g[1]-2,5
g[2]-3
g[3]-none
g[4]-7
g[5]-2,6
g[6]-none
g[7]-none
이렇게 담길 수 있도록 해줬고
이제 몇개가 연결되어 있는지는 dfs나 bfs로 찾아주면 되는데
재방문 하지 않도록 v배열로 체크하면서 이동
여기서는 dfs썼음

*/

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
