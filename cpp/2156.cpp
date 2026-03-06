/** #2156번 포도주 시식
 * dp에 세가지 중 가장 큰값을 저장하는 것
 * 현재 와인을 안마시는 경우, 현재와인 만 마시는경우(이전와인은 안마심), 현재와인과 이전 와인을 마시는 경우
 * 위 셋중 가장 큰 값을 저장, 초기값은 dp[1]에는 1번와인을 마시는 경우
 * dp[2]에는 1번 2번와인을 모두 마시는 경우만 미리 저장해둔다
 * 초기값도 사실 우리가 생각해놓은 알고리즘에 근거하여 설정해주면 됨
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

    vector<int> wine(n+1);
    vector<int>dp(n+1);
    
    for(int i=1;i<=n;i++){
        cin>> wine[i];    
    }

    dp[1]=wine[1];
    if(n>=2){
        dp[2]= wine[1]+ wine[2];
    }

    for(int i=3;i<=n;i++){
        dp[i]=max({dp[i-1],dp[i-2]+wine[i],dp[i-3]+wine[i - 1] + wine[i]});
    }

    cout<<dp[n]<<"\n";

    return 0;
}