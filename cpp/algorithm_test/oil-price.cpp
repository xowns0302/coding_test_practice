/**
 * 먼저 display의 숫자를 세팅해놓고 배열 두개를 비교해서 달라진 값만 찾아주면 됨
 * 배열 복사를 쉽게하려고 memcpy를 사용함
 * void* memcpy(void* dest, const void* src, size_t n);
 */



#include <iostream>
#include <cstring>
using namespace std;

bool dis[10][7] = {
    {1,1,1,1,1,1,0}, // 0
    {0,1,1,0,0,0,0}, // 1
    {1,1,0,1,1,0,1}, // 2
    {1,1,1,1,0,0,1}, // 3
    {0,1,1,0,0,1,1}, // 4
    {1,0,1,1,0,1,1}, // 5
    {1,0,1,1,1,1,1}, // 6
    {1,1,1,0,0,1,0}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,1,0,1,1}  // 9
};

bool first[5][7];
bool second[5][7];

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin>> n;

    for(int k=0; k<n; k++){
        int cnt=0;
        string a,b;
        cin >> a >> b;

        memset(first, 0, sizeof(first));
        memset(second, 0, sizeof(second));

        for(int i=0; i<a.size(); i++){
            memcpy(first[5-i-1], dis[a[a.size()-i-1]- '0'], sizeof(dis[0]));
        }
        for(int i=0; i<b.size(); i++){
            memcpy(second[5-i-1], dis[b[b.size()-i-1]- '0'], sizeof(dis[0]));
        }
        for(int i=0; i<5;i++){
            for(int j=0; j<7; j++){
                if(first[i][j]!=second[i][j]){
                    cnt++;
                }
            }
        }
        cout << cnt << "\n";
    }

    return 0;
}