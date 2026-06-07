/*bfs인거 같음
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int h, w;
vector<vector<int>> image;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

void bfs(int sx, int sy, int newColor) {
    int oldColor = image[sx][sy];
    if (oldColor == newColor) return;

    queue<pair<int,int>> q;
    q.push({sx, sy});
    image[sx][sy] = newColor;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 1 || nx > h || ny < 1 || ny > w) continue;

            if (image[nx][ny] == oldColor) {
                image[nx][ny] = newColor;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> h >> w;

    image.resize(h + 1, vector<int>(w + 1));

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cin >> image[i][j];
        }
    }

    int q;
    cin >> q;

    while (q--) {
        int i, j, c;
        cin >> i >> j >> c;
        bfs(i, j, c);
    }

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) {
            cout << image[i][j] << ' ';
        }
        cout << '\n';
    }
}