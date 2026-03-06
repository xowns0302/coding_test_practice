#include <iostream>

using namespace std;

int N, K;
int dp[102][100002];
int w[102],v[105];
int main(){
    cin>> N>>K;
    for(int i=1; i<=N;i++){
        cin>>w[i]>>v[i];
    }
    for(int i=1;i<=N;i++){
        for(int j=1;j<=K;j++){
            dp[i][j]=dp[i-1][j];
            if(j>=w[i]){
                dp[i][j]=max(dp[i][j],dp[i-1][j-w[i]]+v[i]);
            }
        }
    }
    cout<<dp[N][K];
    return 0;

}