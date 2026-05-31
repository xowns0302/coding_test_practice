#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, T;
    cin >> N >> T;

    while(T--) {
        vector<ll> c(N+1), d(N+1);
        // 입력: c1 d1 c2 d2 ...
        for(int i = 1; i <= N; i++) {
            cin >> c[i];
            if(i < N) cin >> d[i];
        }

        // k개의 세트가 가능한지 체크
        auto check = [&](ll k) -> bool {
            // 레벨 1: d[1]에서 x개를 레벨 1에 배정
            ll x = max(0LL, k - c[1]); // 최소로 필요한 x_1
            if(x > d[1]) return false;

            // 레벨 2 ~ N-1
            for(int i = 2; i < N; i++) {
                ll avail = d[i-1] - x;  // d[i-1]에서 레벨 i로 넘어오는 양
                x = max(0LL, k - c[i] - avail);
                if(x > d[i]) return false;
            }

            // 레벨 N: 남은 d[N-1]이 c[N]과 합쳐서 k 이상이어야 함
            ll avail = d[N-1] - x;
            return c[N] + avail >= k;
        };

        ll lo = 0, hi = 3e12;
        while(lo < hi) {
            ll mid = lo + (hi - lo + 1) / 2;
            if(check(mid)) lo = mid;
            else hi = mid - 1;
        }

        cout << lo << '\n';
    }

    return 0;
}
