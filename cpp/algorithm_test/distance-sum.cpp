#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef long long ll;
typedef pair<int, ll> pil;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    vector<vector<pil>> adj(N+1);
    for(int i = 0; i < N-1; i++) {
        int x, y; ll t;
        cin >> x >> y >> t;
        adj[x].push_back({y, t});
        adj[y].push_back({x, t});
    }

    vector<ll> cnt(N+1, 1);       // 서브트리 크기
    vector<ll> sum_dist(N+1, 0);  // 루트 기준 서브트리 내 거리합
    vector<ll> ans(N+1, 0);
    vector<int> par(N+1, 0);
    vector<ll> par_w(N+1, 0);
    vector<int> order;
    order.reserve(N);

    // BFS로 탐색 순서 및 부모 정보 수집
    vector<bool> visited(N+1, false);
    queue<int> q;
    q.push(1);
    visited[1] = true;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for(auto& e : adj[u]) {
            int v = e.first; ll w = e.second;
            if(!visited[v]) {
                visited[v] = true;
                par[v] = u;
                par_w[v] = w;
                q.push(v);
            }
        }
    }

    // 역순 처리: 자식 → 부모로 cnt, sum_dist 합산
    for(int i = (int)order.size()-1; i >= 1; i--) {
        int v = order[i];
        cnt[par[v]] += cnt[v];
        sum_dist[par[v]] += sum_dist[v] + cnt[v] * par_w[v];
    }

    // BFS 순서로 rerooting: 부모의 ans로 자식 ans 계산
    ans[1] = sum_dist[1];
    for(int u : order) {
        for(auto& e : adj[u]) {
            int v = e.first; ll w = e.second;
            if(v == par[u]) continue;
            ans[v] = ans[u] - cnt[v] * w + (N - cnt[v]) * w;
        }
    }

    for(int i = 1; i <= N; i++) {
        cout << ans[i] << '\n';
    }

    return 0;
}
