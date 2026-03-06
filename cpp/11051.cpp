/** 11051번
 * 이항계수 값을 10,007로 나눈 수는 무엇인지 찾는 문제임
 * 
 * 이항계수 성질인 nCk =(n-1)C(k-1)+(n-1)Ck 이성질을 사용하는데
 * dp[n-1][k-1] + dp[n-1][k]=dp[n][k]
 * 
 */

#include <iostream>
#include <vector>

using namespace std;

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,k;
    cin>>n>>k;

    vector<vector<int>>dp(n+1,vector<int>(k+1,0));

    for(int i=1;i<n+1;i++){
        for(int j=0;j<k+1;j++){
            if(j==0||i==j){
                dp[i][j]=1;
            }else{
                dp[i][j]=(dp[i-1][j-1]+dp[i-1][j])%10007;
            }
        }
    }

    cout<<dp[n][k]<<"\n";
    return 0;
}