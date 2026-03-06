/* BFS 문제*/


#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m,dx,dy;
    cin>>n>>m;
    vector<vector<int>> map(n, vector<int>(m));
    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int,int>> q;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> map[i][j];
            if(map[i][j]==2){
                dx=i;
                dy=j;
            }
        }
    }
    dist[dx][dy]=0;
    q.push({dx,dy});
    int dirx[4] = {1, -1, 0, 0};
    int diry[4] = {0, 0, 1, -1};

    while(!q.empty()){
        auto [x, y] = q.front();
        q.pop();

        for(int k = 0; k < 4; k++){
            int nx = x + dirx[k];
            int ny = y + diry[k];

            if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            if(map[nx][ny] == 0) continue;

            if(dist[nx][ny] != -1) continue;

            dist[nx][ny] = dist[x][y] + 1;
            q.push({nx, ny});
        }

    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(map[i][j] == 0) cout << 0;
            else cout << dist[i][j];

            if(j != m-1) cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}