#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(){
    int T;
    cin >> T;
    while(T--){
        int N, K;
        cin >> N >> K;
        vector<int> cos(N+1); // 건물 건설 시간
        vector<vector<int>> adj(N+1); // 인접 리스트
        vector<int> ind(N+1, 0); // 진입차수
        vector<int> res(N+1, 0); // 각 건물까지의 최대 건설 시간

        for(int i = 1; i <= N; i++){
            cin >> cos[i];
        }

        for(int i = 0; i < K; i++){
            int a, b;
            cin >> a >> b;
            adj[a].push_back(b);
            ind[b]++;
        }

        queue<int> q;
        for(int i = 1; i <= N; i++){
            if(ind[i] == 0){
                q.push(i);
                res[i] = cos[i]; // 진입차수가 0인 노드의 초기 시간 설정
            }
        }

        while(!q.empty()){
            int x = q.front();
            q.pop();
            for(auto nxt : adj[x]){
                res[nxt] = max(res[nxt], res[x] + cos[nxt]); // 누적 최대 시간 갱신
                ind[nxt]--;
                if(ind[nxt] == 0){
                    q.push(nxt);
                }
            }
        }

        int w;
        cin >> w;
        cout << res[w] << endl; // w 건물까지의 최대 건설 시간 출력
    }

    return 0;
}