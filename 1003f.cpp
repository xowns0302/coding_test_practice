//1003번이 시간이 너무 오래걸려서 빠른 버전
//dp썼음
#include <iostream>
#include <vector>

using namespace std;

vector<int> dpz(41, 0);  
vector<int> dpo(41, 0);


int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    dpz[0] = 1, dpz[1] = 0;  
    dpo[0] = 0, dpo[1] = 1;
    for(int i=2;i<41;i++){
        dpz[i]=dpz[i-1]+dpz[i-2];
        dpo[i]=dpo[i-1]+dpo[i-2];
    }
    for(int i=0;i<T;i++){
        int N;
        cin>>N;
        cout<<dpz[N]<<" "<<dpo[N]<<"\n";
    }
    return 0;
}