#include <iostream>

using namespace std;

int cnt =0;
int r,c;

void z(int x, int y, int size){
    if(size == 1){
        cout << cnt << "\n";
        return;
    }

    int half = size / 2;

    if(r < x + half && c < y + half){
        z(x, y, half);
    }
    else if(r < x + half && c >= y + half){
        cnt += half * half;
        z(x, y + half, half);
    }
    else if(r >= x + half && c < y + half){
        cnt += 2 * half * half;
        z(x + half, y, half);
    }
    else{
        cnt += 3 * half * half;
        z(x + half, y + half, half);
    }
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n >> r >> c;
    int size = 1 << n;

    z(0,0,size);

    return 0;
}