#include <iostream>
#include <vector>
using namespace std;

int N;
vector<vector<int>> map;
vector<vector<int>> visited;

int jelly(int x, int y) {
    if (x == N - 1 && y == N - 1)
        return 1;

    visited[x][y] = 1;
    int result = 0;

    if (x + map[x][y] < N && !visited[x + map[x][y]][y]) {
        result |= jelly(x + map[x][y], y);
    }
    if (y + map[x][y] < N && !visited[x][y + map[x][y]]) {
        result |= jelly(x, y + map[x][y]);
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    map.assign(N, vector<int>(N));
    visited.assign(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
        }
    }

    int result = jelly(0, 0);

    if (result == 1) cout << "HaruHaru\n";
    else cout << "Hing\n";

    return 0;
}
