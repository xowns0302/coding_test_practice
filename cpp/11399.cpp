#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int N;
    int r=0;
    vector <int>p;
    cin>>N;
    for(int i=0;i<N;i++){
        int a;
        cin>>a;
        p.push_back(a);
    }
    sort(p.begin(),p.end());
    for(int i=0;i<N;i++){
        int s=0;
        for(int j=i;j>=0;j--){
            s+=p[j];
        }
        r+=s;
    }
    cout<<r;
    return 0;
}