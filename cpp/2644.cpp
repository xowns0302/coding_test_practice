/**#2644번 촌수 계산
 * 그냥 촌수만 계산하면 되는데 쉽게 갈 수 있는 방법이 있는가?
 * 입력은 또 어떻게 받지?
 * 일단 양방향으로 입력 다받아놓고 왜냐면 다시 돌아갈 수도있도록
 * 
 * 
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int person,a,b,rel;
    cin>>person>>a>>b>>rel;
    vector<vector<int>>graph(person+1);
    vector<int>visited(person+1,-1);

    for(int i=0;i<rel;i++){
        int x,y;
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    queue<int>q;
    q.push(a);
    visited[a]=0;

    while (!q.empty()) {
        int cur = q.front(); 
        q.pop();

        for (int next : graph[cur]) {
            if (visited[next] == -1) {
                visited[next] = visited[cur] + 1;
                q.push(next);
            }
        }
    }

    cout<<visited[b]<<"\n";
    return 0;
}
