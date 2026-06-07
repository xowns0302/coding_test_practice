#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;
typedef long long ll;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    cin >> N;

    // 이벤트: (크기 S, 소비자 인덱스, 가격 P)
    vector<tuple<int,int,ll>> events;

    for(int i = 0; i < N; i++) {
        int A;
        cin >> A;
        for(int j = 0; j < A; j++) {
            int S; ll P;
            cin >> S >> P;
            events.emplace_back(S, i, P);
        }
    }

    // S 기준 정렬
    sort(events.begin(), events.end());

    // 각 소비자의 현재 최대 가격 (초기값 0)
    vector<ll> cur_max(N, 0LL);
    ll total = 0;

    // (S_value, 누적매출) 리스트 — 매출이 바뀔 때만 기록
    vector<pair<int,ll>> rev_list;
    vector<ll> revenues; // binary search용

    int idx = 0, ne = (int)events.size();
    while(idx < ne) {
        int cur_S = get<0>(events[idx]);
        // 같은 S의 이벤트 모두 처리
        while(idx < ne && get<0>(events[idx]) == cur_S) {
            int ci = get<1>(events[idx]);
            ll p  = get<2>(events[idx]);
            if(p > cur_max[ci]) {
                total += p - cur_max[ci];
                cur_max[ci] = p;
            }
            idx++;
        }
        // 매출이 바뀐 경우만 기록 (중복 S 제거)
        if(rev_list.empty() || rev_list.back().second != total) {
            rev_list.emplace_back(cur_S, total);
            revenues.push_back(total);
        }
    }

    ll max_rev = rev_list.empty() ? 0LL : rev_list.back().second;

    int M;
    cin >> M;

    for(int q = 0; q < M; q++) {
        if(q > 0) cout << ' ';
        ll Q;
        cin >> Q;

        if(Q > max_rev) {
            cout << -1;
        } else {
            // 매출 >= Q인 첫 번째 인덱스 찾기
            int pos = (int)(lower_bound(revenues.begin(), revenues.end(), Q) - revenues.begin());
            cout << rev_list[pos].first;
        }
    }
    cout << '\n';

    return 0;
}
