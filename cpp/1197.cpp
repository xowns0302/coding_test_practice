#include <iostream>
#include <vector>
#include <queue>

using namespace std;
template<typename T>
using priority_stack=priority_queue<T,vector<T>,greater<T>>;
int v,e;
const int s_max=1000002;
int p[s_max];
int depth[s_max];
bool merge(int,int);
int find(int);

int main(){
    cin.tie(0);
    cout.tie(0);
    ios_base::sync_with_stdio(false);
    
    cin>>v>>e;
    priority_stack<pair<int,pair<int,int>>>edges;
    for(int i=1;i<=v;i++){
        p[i]=i;
        depth[i]=0;
    } 
    while(e--){
        int a,b,c;
        cin>>a>>b>>c;
        edges.push({c,{a,b}});
    }
    long long ans =0;
    while(!edges.empty()){
        
        ans+=edges.top().first*merge(edges.top().second.first,edges.top().second.second);
        edges.pop();
    }

    cout<<ans;
    return 0;
}

bool merge(int x, int y){
    int ans_x=find(x);
    int ans_y=find(y);
    if(ans_x==ans_y) return false;
    else{
        if(depth[ans_x]>depth[ans_y])p[ans_y]=ans_x;
        else if(depth[ans_x]<depth[ans_y])p[ans_x]=ans_y;
        else{
            p[ans_y]=ans_x;
            depth[ans_x]++;
        }
        return true;
    }
}

int find(int x){
    if(p[x]==x){
        return x;
    }
    return p[x] = find(p[x]);
}