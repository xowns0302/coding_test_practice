#include <iostream>

using namespace std;

int n,m;
const int s_max=1000002;
int p[s_max];
void merge(int,int);
int find(int);

int main(){
    cin>>n>>m;
    for(int i=0; i<=n;i++){
        p[i]=i;
    }
    for(int i=0,op,a,b; i<m;i++){
        cin>>op>>a>>b;
        if(!op){
            merge(a,b);
        }else{
            if(find(a)==find(b)){
                cout<<"YES\n";
            }else{
                cout<<"NO\n";
            }
        }
    }
    return 0;
}

void merge(int x, int y){
    x=find(x);
    y=find(y);
    p[y]=x;
}

int find(int x){
    if(p[x]==x){
        return x;
    }
    return p[x] = find(p[x]);
}