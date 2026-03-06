#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>>n;
    priority_queue<int,vector<int>, greater<int>> pq;

    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        if(a==0&&pq.empty()){
            cout<<"0"<<"\n";
        }else if(a==0){
            cout<<pq.top()<<"\n";
            pq.pop();
        }
        else{
            pq.push(a);
        }
    }

    return 0;
}