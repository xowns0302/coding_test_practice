#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, M, K;
    cin >> N >> M >> K;

    vector<int> A(N), B(M);
    for(int i = 0; i < N; i++) cin >> A[i];
    for(int j = 0; j < M; j++) cin >> B[j];

    // dp[i][j]: A[i-1]과 B[j-1]로 끝나는 공통 substring 최대 길이
    vector<vector<int>> dp(N+1, vector<int>(M+1, 0));
    int ans = 0;

    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= M; j++) {
            if(A[i-1] == B[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                ans = max(ans, dp[i][j]);
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
