/** #24479번 알고리즘 수업- 깊이우선 탐색 1
 * 
 * 
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(vector<int>&V, const vector<vector<int>>& E, int R, int& cnt);

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N,M,R;
    cin>>N>>M>>R;
    vector<int>visited(N+1,0);
    vector<vector<int>>graph(N+1);

    for(int i=0;i<M;i++){
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for (auto& row : graph) {// 행을 정렬해줌으로써 오름차순으로 먼저 노드에 접근하도록 함
        sort(row.begin(), row.end());
    }
    int cnt=1;
    dfs(visited, graph, R, cnt);

    for(int i=1;i<=N;i++){
        cout<<visited[i]<<"\n";
    }
    
    return 0;
}

void dfs(vector<int>& V, const vector<vector<int>>& E, int R, int& cnt) {
    V[R] = cnt++;

    for (int next : E[R]) { // R에 연결된 노드들만 순회
        if (V[next]==0) {
            dfs(V, E, next, cnt);
        }
    }
}
