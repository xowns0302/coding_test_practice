/** #1149번 RGB거리
 * 앞뒤 집은 색이 같으면 안된다
 * 집의 갯수/ 각 집을 R,G,B 로 칠할때의 비용이 순서대로 주어짐
 * 모든 집을 칠했을때의 최솟값을 구해라
 * 
 * 조건: 최솟 값을 구해야함 각 줄마다 최솟값은 존재
 * 최솟값만 고르다 보면 색이 겹치는 경우 발생 
 * 벡터는 2차원 벡터로
 * 
 * 2차원 dp를 사용하면 되는 거임
 * 모든 경우의 수를 다 dp에 저장해놓고 사용하는거임
 * 먼저 첫번째 집에 색칠하는 경우를 전부 dp에 깔아놓고
 * 두번째 집 색칠할때에는 앞에 저장해놓은 값들 중에서
 * 만약에 두번째 집에 빨간색을 색칠할 경우 앞에 저장한 것들 중 초록, 파랑 중에서 작은 값을 골라와서
 * 빨간색 가격과 더해주고 값을 저장 두번째 집에 초록색을 칠할 경우 빨강, 파랑 중에서 작은값 선택
 * 초록색 가격과 더해주고 값을 저장하는 식으로 모든 값을 저장한다.
 * 
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    vector <vector<int>>cost(n,vector<int>(3));
    vector <vector<int>>dp(n,(vector<int>(3)));

    for(int i=0;i<n;i++){
        cin>>cost[i][0]>>cost[i][1]>>cost[i][2];
    }
    
    dp[0][0] =cost[0][0];
    dp[0][1] =cost[0][1];
    dp[0][2] =cost[0][2];

    for(int i=1;i<n;i++){
        dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + cost[i][0];
        dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + cost[i][1];
        dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + cost[i][2];
    }
    
    cout<<min({dp[n-1][0], dp[n-1][1], dp[n-1][2]}) << '\n';


    return 0;
}