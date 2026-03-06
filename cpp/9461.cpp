/** #9461 파도반 수열 
 * 삼각형이 나선 모양으로 놓여져있다. 첫 삼각형으로 변의 길이는 1이다. 
 * 그 다음 다음과같은 과정으로 정삼각형을 계속 추가한다 나선에서 가장 긴 변의 길이를 k라 했을 때 
 * 그 변에 길이가 k 인 정삼각형을 추가한다.
 * 
 * 내가 지금 딱 봤을 때 생각난 풀이는 일반항을 설정하는 것
 * n개의 항이 있을 때, n+1=(n-1)+(n-2) 인 걸 dp로 하는 간단한 문제 같음
 * n은 100개 까지 가능하댔으니깐 vector 사이즈는 101로 잡아주겠음
*/

#include <iostream> 
#include <vector>

using namespace std;

vector <long long> dp={0,1,1};

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    dp.resize(101);

    for(int i=3; i<101;i++){
        dp[i]=dp[i-2]+dp[i-3];
    }

    int t;
    cin>>t;
    while(t--){    
        int a;
        cin>>a;
        cout<<dp[a]<<"\n";
    }
    return 0;
}