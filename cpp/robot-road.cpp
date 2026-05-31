#include <iostream>
#include <vector>
#include <string>
using namespace std;

int H, W;
vector<string> grid;

// 방향: 0=N, 1=E, 2=S, 3=W
int DR[] = {-1, 0, 1, 0};
int DC[] = {0, 1, 0, -1};
char DIR_CHAR[] = {'^', '>', 'v', '<'};

bool is_hash(int r, int c) {
    return r >= 0 && r < H && c >= 0 && c < W && grid[r][c] == '#';
}

int get_dir(int dr, int dc) {
    for(int d = 0; d < 4; d++)
        if(DR[d] == dr && DC[d] == dc) return d;
    return -1;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> H >> W;
    grid.resize(H);
    for(int i = 0; i < H; i++) cin >> grid[i];

    // 끝점 찾기: '#' 이웃이 정확히 1개인 셀
    vector<pair<int,int>> endpoints;
    for(int r = 0; r < H; r++) {
        for(int c = 0; c < W; c++) {
            if(grid[r][c] != '#') continue;
            int cnt = 0;
            for(int d = 0; d < 4; d++)
                if(is_hash(r + DR[d], c + DC[d])) cnt++;
            if(cnt == 1) endpoints.push_back({r, c});
        }
    }

    // 각 끝점에서 출발 시도
    for(int ei = 0; ei < (int)endpoints.size(); ei++) {
        int sr = endpoints[ei].first, sc = endpoints[ei].second;

        // 체인을 따라 경로 추출
        vector<pair<int,int>> path;
        vector<vector<bool>> vis(H, vector<bool>(W, false));
        path.push_back({sr, sc});
        vis[sr][sc] = true;

        while(true) {
            int r = path.back().first, c = path.back().second;
            bool found = false;
            for(int d = 0; d < 4; d++) {
                int nr = r + DR[d], nc = c + DC[d];
                if(is_hash(nr, nc) && !vis[nr][nc]) {
                    path.push_back({nr, nc});
                    vis[nr][nc] = true;
                    found = true;
                    break;
                }
            }
            if(!found) break;
        }

        int n = path.size();
        if(n % 2 == 0) continue; // '#' 수는 항상 홀수여야 함
        int k = (n - 1) / 2;    // A 명령 횟수

        // 유효성 검사: j번째 A 명령의 두 스텝이 같은 방향인지
        bool valid = true;
        for(int j = 1; j <= k; j++) {
            int dr1 = path[2*j-1].first  - path[2*j-2].first;
            int dc1 = path[2*j-1].second - path[2*j-2].second;
            int dr2 = path[2*j].first    - path[2*j-1].first;
            int dc2 = path[2*j].second   - path[2*j-1].second;
            if(dr1 != dr2 || dc1 != dc2) { valid = false; break; }
        }
        if(!valid) continue;

        // 초기 방향 및 명령어 생성
        int start_dir = get_dir(path[1].first - path[0].first,
                                 path[1].second - path[0].second);
        int cur_dir = start_dir;
        string cmds = "";

        for(int j = 1; j <= k; j++) {
            int aj_dir = get_dir(path[2*j-1].first - path[2*j-2].first,
                                  path[2*j-1].second - path[2*j-2].second);
            if(aj_dir != cur_dir) {
                // 왼쪽: (cur+3)%4, 오른쪽: (cur+1)%4
                if((cur_dir + 3) % 4 == aj_dir) cmds += 'L';
                else cmds += 'R';
                cur_dir = aj_dir;
            }
            cmds += 'A';
        }

        cout << (sr + 1) << " " << (sc + 1) << "\n";
        cout << DIR_CHAR[start_dir] << "\n";
        cout << cmds << "\n";
        return 0;
    }

    return 0;
}
