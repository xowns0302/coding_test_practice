//그리디 알고리즘
//거스름돈 갯수 구하는 문제
#include <iostream>
#include <vector>

using namespace std;

vector<int>coin={500,100,50,10,5,1};

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int pay;
    int result=0;
    int mon=1000;
    cin>>pay;
    int tmp=mon-pay;
    for(auto data: coin){
        result+=tmp/data;
        tmp=tmp%data;
    }
    cout<<result;
    return 0;
}

