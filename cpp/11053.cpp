/**#11053번 가장긴 증가하는 부분수열
 * dp 배열에다가 i 번째까지의 수열 모든 조합 중 가장 긴 길이만 dp에 저장
 * for를 2중으로 돌려서 j를 돌리면서 시작점을 다르게 해주는 방식 
 * j번째부터 i번째까지 돌면서 i 번째 숫자가 j 번째 숫자보다 더 큰지 비교하고,
 * 그 j 번째에 있는 dp+1 값이랑 i번째에 있는 dp값을 비교해서 더큰값을 새로 i번째 dp에 업데이트
 * i = 1, A[1] = 20
 *  A[0] = 10 < 20 → dp[1] = max(1, dp[0]+1) = 2
 *  → dp = [1, 2, 1, 1, 1, 1]
 * i = 2, A[2] = 10
 *  A[0]=10은 같음 (증가 아님), A[1]=20 > 10 → 건너뜀
 *  → dp[2] = 1
 * i = 3, A[3] = 30
 *  A[0]=10 < 30 → dp[3] = max(1, dp[0]+1) = 2
 *  A[1]=20 < 30 → dp[3] = max(2, dp[1]+1) = 3
 *  A[2]=10 < 30 → dp[3] = max(3, dp[2]+1) = 3
 *  → dp = [1, 2, 1, 3, 1, 1]
 * i = 4, A[4] = 20
 *  A[0]=10 < 20 → dp[4]=2
 *  A[2]=10 < 20 → dp[4]=2 (동일)
 *  → dp = [1, 2, 1, 3, 2, 1]
 * i = 5, A[5] = 50
 *  A[0]=10 < 50 → dp[5]=2
 *  A[1]=20 < 50 → dp[5]=3
 *  A[3]=30 < 50 → dp[5]=4
 *  → dp = [1, 2, 1, 3, 2, 4]
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main (void){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    vector <int>dp( 1000 ,1);
    vector<int>A(1000);
    int n;
    int m=0;
    cin>>n;

    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        A[i]=a;
    }

    for(int i=0;i<n;i++){
        
        for(int j=0;j<i;j++){
            if(A[j]<A[i]){
                dp[i] = max(dp[i],dp[j]+1);
            }
        }
        if(m<dp[i]){
            m=dp[i];
        }
    }
    cout<<m<<"\n";
    return 0;
}