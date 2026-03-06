//외판원 순회 BOJ #2098
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int INF=1e9;
 
int dp[20][1<<20];
int w[20][20];
int dfs(int, int);
int n;

int main(){
    cin>>n;
    for(int i=0; i<n;i++){
        for(int j=0; j<n;j++){
            cin>>w[i][j];
        }
        fill(dp[i],dp[i]+(1<<20),INF);
    }
    cout<<dfs(0,1);
}

int dfs(int i, int s){
    int &res=dp[i][s];
    if(res !=INF) return res;
    
    for(int j=0;j<n;j++){
        if(w[i][j]==0)continue;
        if((s>>j)&1)continue;
        res = min(res, dfs(j,s|(1<<j))+w[i][j]);
    }
    if(res==INF)return w[i][0];
    
    return res;
}