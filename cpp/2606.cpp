/** #2606번 바이러스
 * 모든 경우를 다 탐색해야하는 경우 그래프에서는 dfs를 사용하는게 적합해 보임
 * bfs는 최단거리.
 * 
 * 2차원 그래프에 먼저 입력을 받는데 입력을 받을 때
 * 1 2 5
 * 2 3
 * 3
 * 4 7
 * 5 2 6
 * 6 
 * 7
 * 이렇게 받아놓음
 * 그리고 연결된 노드들을 타고가는 부분은 dfs이기때문에 stack 알고리즘을 사용해줬음
 * 그리고 접근했을때 노드가 visited가 true 이면 그냥 넘어가는 걸로 해서 이미 접근한 노드는 제외
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    int com,pair;
    cin>>com>>pair;
    vector<vector<int>>dfs(com+1);
    vector<bool>visited(com+1,false);
    for(int i=0;i<pair;i++){
        int col,row;
        cin>>col>>row;
        dfs[col].push_back(row);
        dfs[row].push_back(col);
    }
    
    stack<int>s;
    s.push(1);
    visited[1]=true;
    int infected=0;

    while(!s.empty()){
        int cur =s.top(); 
        s.pop();

        for(int next: dfs[cur]){
            if(!visited[next]){
                visited[next]=true;
                infected++;
                s.push(next);
            }
        }

    }

    cout<<infected<<"\n";
    return 0;
}