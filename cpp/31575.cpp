/** #31575번 도시와 비트코인
 * 왼쪽 위가 진우 오른쪽 가장 아래가 거래소
 * 
 * 1로 표시된 곳은 갈 수 있는 곳 0은 갈수 없는 곳
 * 거래소로 갈 수 있으면 yes 갈 수 없으면 no
 * 빨리가는 건 중요하지 않음 그냥 도착할 수 있는지 여부가 중요함
 * 따라서 dfs를 사용하겠음
 * 
 * 이동은 오른쪽이랑 아래로만 이동가능
 * 그냥 다 보낼수 있으면 다보내는 식으로 탐색
 * 재귀함수를 사용해도 될거 같기도함
 * 
 */


#include <iostream>
#include <vector>
using namespace std;
bool search(int y, int x, vector<vector<int>>& map, vector<vector<bool>>& visited, int m, int n);
int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin>>n>>m;
    vector<vector<int>>map(m,vector<int>(n));
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            cin>>map[i][j];
        }
    }
    if(search(0,0,map,visited,m,n))cout<<"Yes\n";
    else cout<< "No\n";

    return 0;
}

bool search(int y, int x, vector<vector<int>>& map, vector<vector<bool>>& visited, int m, int n) {
    if (y >= m || x >= n || map[y][x] == 0|| visited[y][x])//여기서 map에서 1인값만 지속적으로 탐색하도록함
        return false;

    if (y == m - 1 && x == n - 1)
        return true;
    visited[y][x]=true;
    return search(y + 1, x, map, visited, m, n) || search(y, x + 1, map, visited, m, n);
}
