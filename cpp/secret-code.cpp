/* 일단 0,0 부터 시작
    a는 type 인덱스, b는 code 인덱스
    mach(0,0);에서 만약 다르면 type 인덱스만 증가, code 인덱스는 유지
    같으면 둘 인덱스 동시 증가 만약 같다가 다르면 인덱스 초기화
    result로 이미 찾았으면 바로 종료 이방법은 너무 복잡함
*/

/*#include <iostream>
#include <vector>

using namespace std;

vector<int> code;
vector<int> type;
bool result = false;

void match(int a, int b){
    if (result) return;
    if (a >= type.size()) return;

    if (b >= code.size()) {
        result = true;
        cout << "secret\n";
        return;
    }

    if (type[a] == code[b]) {
        match(a + 1, b + 1);
    } else {
        match(a + 1, 0);
    }
}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m,k;
    cin >> m >> n >> k;
    code.resize(m);
    type.resize(n);
    for(int i=0; i<m;i++){
        cin >> code[i];
    }
    for(int i=0; i<n; i++){
        cin >> type[i];
    }

    if(type.size() < code.size()){
        cout<<"normal"<<"\n";
        return 0;
    }else{
        match(0,0);
        if (!result){
            cout<<"normal"<<"\n";
        }
    }
    return 0;
}*/

/* 최대한 간단하게

*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int m, n, k;
    cin >> m >> n >> k;

    vector<int> code(m), type(n);

    for (int i = 0; i < m; i++) cin >> code[i];
    for (int i = 0; i < n; i++) cin >> type[i];

    if (n < m) {
        cout << "normal\n";
        return 0;
    }

    for (int i = 0; i <= n - m; i++) {
        //secret code가 존재 하려면 최소한 n-m 안에 비밀 코드의 첫번째 코드가 시작 돼야함
        bool flag = true;
        for (int j = 0; j < m; j++) {
            //어쨌든 비교를 시작한 지점 부터 연속된 녀석이 나와야하니깐 type에서 모든 자리에서 비교 해도 수행횟수가 그리 많지 않음
            if (type[i + j] != code[j]) {//s.c가 연속 아니거나 다르면 break.
                flag = false;
                break;
            }
        }
        if (flag) {
            cout << "secret\n";
            return 0;
        }
    }

    cout << "normal\n";
    return 0;
}