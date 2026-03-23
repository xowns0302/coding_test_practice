/**
 * 걍 노가다 인듯
 * 맵으로 id가 어디 얹었는지 기록만 하고
 * 앉을 수 있는 자리 전체 돌리면서 해당 자리에서 가장 가까운 사람과의 거리 구하고
 * 앉을 수 있는 자리 중 가장 안전도 높은 값 찾아서 해당 좌표로 앉히기
 */

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

int n, m;
bool seat[21][21];
map<int, pair<int, int>> id_map;
int id_list[10001];

int get_distance(int r, int c) {
    int min_distance = INT_MAX;
    for(auto const& [id, pos] : id_map) {
        int dr = pos.first - r;
        int dc = pos.second - c;
        int dist_sq = dr * dr + dc * dc;
        if(dist_sq < min_distance) min_distance = dist_sq;
    }
    return min_distance;
}

bool find_seat(int x) {
    if (id_map.empty()) {
        seat[1][1] = true;
        id_map[x] = {1, 1};
        return true;
    }

    int max_safe_distance = -1;
    int temp_x = -1, temp_y = -1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (seat[i][j]) continue;

            bool adj = false;
            int dx[] = {-1, 1, 0, 0};
            int dy[] = {0, 0, -1, 1};
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if (ni >= 1 && ni <= n && nj >= 1 && nj <= m && seat[ni][nj]) {
                    adj = true; break;
                }
            }
            if (adj) continue;

            int current_safety = get_distance(i, j);
            if (current_safety == -1) continue; 

            if (current_safety > max_safe_distance) {
                max_safe_distance = current_safety;
                temp_x = i; temp_y = j;
            }
        }
    }

    if (temp_x == -1) return false;

    seat[temp_x][temp_y] = true;
    id_map[x] = {temp_x, temp_y};
    return true;
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int q;
    cin>> n >> m >> q;
    for(int i=0;i<q;i++){
        string f;
        int id;
        cin>>f>>id;
        if (f == "In") {
            if (id_list[id] == 0) {
                if (find_seat(id)) {
                    id_list[id] = 1; 
                    cout << id << " gets the seat (" << id_map[id].first << ", " << id_map[id].second << ").\n";
                } else {
                    cout << "There are no more seats.\n";
                }
            } else if (id_list[id] == 1) {
                cout << id << " already seated.\n";
            } else if (id_list[id] == 2) {
                cout << id << " already ate lunch.\n";
            }
        } else if (f == "Out") {
            if (id_list[id] == 0) {
                cout << id << " didn't eat lunch.\n";
            } else if (id_list[id] == 1) {
                pair<int, int> pos = id_map[id];
                seat[pos.first][pos.second] = false;
                id_map.erase(id);
                id_list[id] = 2;
                cout << id << " leaves from the seat (" << pos.first << ", " << pos.second << ").\n";
            } else if (id_list[id] == 2) {
                cout << id << " already left seat.\n";
            }
        }
    }


    return 0;
}