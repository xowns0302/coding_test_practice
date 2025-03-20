#include <iostream>
//이건 그냥 노멀한 방식으로 한 1만들기
// 연산횟수의 최소를 구하려면 다른 방식이 필요함
// 그건 1463f.cpp에서 다루겠음
using namespace std;

int main(){
    long long N;
    cin>>N;
    int count=0;
    while(N>1){
        count++;
        if(!(N%3)){
            N=N/3;
            cout<<N<<"\n";
        }else if(!(N%2)){
            N=N/2;
            cout<<N<<"\n";
        }else{
            N=N-1;
            cout<<N<<"\n";
        }
    }
    cout<<count;
    return 0;
   
}