/** #24444번 bfs
 * 이문제는 주어진 트리를 너비우선 탐색을 통해 접근 순서를 출력하는 문제
 * 먼저 너비우선 탐색이므로 queue를 사용하는데
 * 큐에 시작 정점을 먼저 넣고 그 시작 정점을 pop하면서 시작 정점과
 * 간선으로 연결된 정점들을 오름차순으로 방문한다
 * 내가 고민하고 있는 부분은 어떻게 재귀로 이것을 나타낼지 인데
 * 시작 정점을 pop하는 순간 연결된 정점을 모두 queue에 담아준다 그리고 
 * queue에 담긴 정점을 하나씩 pop하면서 그 pop된 정점과 간선으로 연결된 정점들을
 * 다시 queue에 담아주는 방식
 * 이 queue가 다 비워질때까지 반복하는 방식으로 하면 된다 재귀로 할 필요없음
 * visited vector를 출력 순서를 담는 칸으로 사용하면 될거 같음
 * 방문한 적 없으면 초기엔 다0으로 세팅
 * 이후 방문하면 방문 순서를 배열에 담아버리는 것
 * 
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int cnt=0;

void bfs(vector<vector<int>>&graph,vector<int>&visited,int R){
    
    queue<int>q;
    visited[R]=++cnt;
    q.push(R);

    while(!q.empty()){
        int n = q.front();
        q.pop();

        for(int next:graph[n]){
            if(visited[next]==0){
                visited[next]=++cnt;
                q.push(next);
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N,M,R;
    cin>>N>>M>>R;
    
    vector<vector<int>>graph(N+1);
    vector<int>visited(N+1,0);

    for(int i=0;i<M;i++){
        int a,b;
        cin>>a>>b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (auto& row : graph) {// 행을 정렬해줌으로써 오름차순으로 먼저 노드에 접근하도록 함
        sort(row.begin(), row.end());
    }

    bfs(graph,visited,R);

    for(int i=1;i<=N;i++){
        cout<<visited[i]<<"\n";
    }

    return 0;
}