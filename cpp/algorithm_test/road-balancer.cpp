#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    long long K;
    cin >> N >> K;

    vector<int> r(N+1);
    vector<vector<int>> children(N+1);
    vector<int> indegree(N+1, 0);

    for(int i = 1; i <= N; i++) {
        cin >> r[i];
        children[i].resize(r[i]);
        for(int j = 0; j < r[i]; j++) {
            cin >> children[i][j];
            indegree[children[i][j]]++;
        }
    }

    vector<long long> cnt(N+1, 0);
    cnt[1] = K;

    // 위상정렬 (Kahn's algorithm)
    queue<int> q;
    for(int i = 1; i <= N; i++) {
        if(indegree[i] == 0) q.push(i);
    }

    while(!q.empty()) {
        int u = q.front(); q.pop();

        if(r[u] > 0) {
            long long base = cnt[u] / r[u];
            long long extra = cnt[u] % r[u];
            for(int j = 0; j < r[u]; j++) {
                // 위치 j(0-indexed): extra보다 작으면 1개 더 받음
                cnt[children[u][j]] += base + (j < extra ? 1 : 0);
                if(--indegree[children[u][j]] == 0) {
                    q.push(children[u][j]);
                }
            }
        }
    }

    for(int i = 1; i <= N; i++) {
        cout << cnt[i];
        if(i < N) cout << ' ';
    }
    cout << '\n';

    return 0;
}
