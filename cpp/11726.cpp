//dp문제로 점화식을 찾아서 그식에 맞는 값을 dp로 만들어놓고 함
//근데 이런 문제는 그냥 외우는건가 이게 피보나치 인걸 어케 알지?

#include <iostream>
#include <vector>

using namespace std;

vector <int>dp={0,1,2};

int main(){
    int n;
    cin>>n;
    dp.resize(n+1);
    for(int i=3;i<=n;i++){
        dp[i]=(dp[i-1]+dp[i-2])%10007;
    }
    
    cout<<dp[n];
    
    return 0;
}