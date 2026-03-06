/** #1260번 dfs와 bfs
 * 
 */
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

vector <vector<int>> graph;
vector <bool> visited1;
vector <bool> visited2;

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited2[start] = true;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << cur << " "; // 방문 순서 출력

        for (int next : graph[cur]) {
            if (!visited2[next]) {
                visited2[next] = true;
                q.push(next);
            }
        }
    }
}
void dfs(int cur) {
    visited1[cur] = true;
    cout << cur << " "; // 방문 순서 출력

    for (int next : graph[cur]) {
        if (!visited1[next]) {
            dfs(next);
        }
    }
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N,M,V;
    cin>>N>>M>>V;
    graph.resize(N+1);
    visited1.resize(N+1,false);
    visited2.resize(N+1,false);
    for(int i=0;i<M;i++){
        int a,b;
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (auto& row : graph) {// 행을 정렬해줌으로써 오름차순으로 먼저 노드에 접근하도록 함
        sort(row.begin(), row.end());
    }
    dfs(V);
    cout<<"\n";
    bfs(V);
    cout<<"\n";


    return 0;
}