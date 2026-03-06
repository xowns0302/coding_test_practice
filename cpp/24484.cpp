/** #24484번 알고리즘 수업- 깊이 우선 탐색 6
 * dfs=stack 알고리즘
 * undirected graph
 * 해당 노드의 depth와 노드 방문 순서인 t를 곱해서 결괏값 출력
 * 22479번과 차이점은 depth를 구해야한다는 건데..
 * depth 구현을 어떻게 하면 좋을까
 * 재귀에 들어가면 depth 값을 +1 해서 넘겨주면서 깊이를 증가시켜줌 
 * 깊이 관리를 해주면 됨
 * 
 * 계속 틀렸던 이유. 
 * 결괏값이 곱해지는 값이 int 값이라 명시적 형변환을 고려했어야함
 * 그래서 곱하기 1LL 해주면 값이 변환됨
 */


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(vector<int>& V, const vector<vector<int>>& E, vector<int>&D, int R, int& cnt, int d);

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N,M,R;
    cin>>N>>M>>R;

    vector<vector<int>>graph(N+1);
    vector<int>visited(N+1,0);
    vector<int>depth(N+1,-1);

    for(int i=0;i<M;i++){
        int a,b;
        cin>>a>>b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (auto& row : graph) {// 행을 정렬해줌으로써 내림차순으로 먼저 노드에 접근하도록 함
        sort(row.begin(), row.end(),greater<int>());
    }


    int cnt=1;
    int d=0;
    dfs(visited,graph,depth,R,cnt,d);
    long long result=0;
    for(int i=1; i<=N;i++){
        result+=1LL *visited[i]*depth[i];
    }
    cout<<result<<"\n";
    return 0;
}

void dfs(vector<int>& V, const vector<vector<int>>& E, vector <int>&D,int R, int& cnt, int d) {
    V[R] = cnt++;
    D[R]=d;
    for (int next : E[R]) { // R에 연결된 노드들만 순회
        if (V[next]==0) {
            dfs(V, E, D, next, cnt, d+1);
        }
    }
    
}
