/*재귀함수*/

#include <iostream>

using namespace std;

int n;
int white =0, blue =0;
int paper[128][128];

void cs(int s,int x,int y){
    int a = paper[x][y];
    bool same = true;

    for(int i=0; i<s;i++){
        for(int j=0; j<s;j++){
            if(a != paper[x + i][y + j]){
                same = false;
                break;
            }
        }
        if(!same) break;
    }
    if(same){
        if(a == 0) white++;
        else blue++;
        return;
    }
    int half = s / 2;
    cs(half, x, y);
    cs(half, x + half, y);
    cs(half, x, y + half);
    cs(half, x + half, y + half);
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n;

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>paper[i][j];
        }
    }
    cs(n,0,0);

    cout<<white<<"\n"<<blue<<"\n";
    return 0;

}
