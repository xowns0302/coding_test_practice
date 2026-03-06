/** #1697번 숨바꼭질
 * 수빈은 동점 동생은 정점 이동은 수빈 +- 1, or 현위치 2배
 * 트리를 만드는데 3가지로 뻗어나감
 * 1자식 두배, 2자식 -1, 3자식 +1
 * 그리고 여기서 탐색을 각각 bfs로 진행
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

    int N,K;
    cin>>N>>K;
    vector<bool> visited (100001,false);
    queue<pair<int,int>> q;

    q.push({N,0});
    visited[N]=true;

    while(!q.empty()){
        int position =q.front().first;
        int time=q.front().second;
        q.pop();

        if(position==K){
            cout<<time<<"\n";
            return 0;
        }

        int nextposition[3]={position-1,position+1,position*2};
        for( int i=0;i<3;i++){
            int next =nextposition[i];
            if(next>=0&&next<=100000&&!visited[next]){
                visited[next]=true;
                q.push({next,time+1});
            }
        }
    }

    return 0;
}