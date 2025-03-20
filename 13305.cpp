//그리디 알고리즘
//기름값 최솟값찾기

#include <iostream>
#include <vector>

using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int node;
    int min=100000;
    int city;
    long long cost=0;
    vector<int>dis(100000);
    cin>>node;
    for(int i=0;i<node-1;i++){
        cin>>dis[i];
    }
    for(int i=0;i<node;i++){
        cin>>city;
        if(i==0||min>city)min=city;
        cost += dis[i]*(long long)min;
    }
    cout<<cost;
    return 0;
}
