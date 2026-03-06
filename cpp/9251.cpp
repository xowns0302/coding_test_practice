#include <iostream>

using namespace std;

string A,B;
int dp [4002][4002];

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>A>>B;
    
    for(int i=1;i<=A.size();i++){
        for(int j=1;j<=B.size();j++){
            if(A[i-1]==B[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
            }else{
                dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
            }
        }
    }
    cout<<dp[A.size()][B.size()];
    return 0;
}