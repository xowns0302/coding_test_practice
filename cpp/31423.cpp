/** #31423번 신촌 통폐합
 * 단순하게 풀수도 있지만 dfs를 활용하여 풀었음
 * 연결되는 이름들로 트리를 구성하고 그 트리의 루트 원소를 찾아줌
 * 그리고 그 루트를 시작으로 dfs를 돌려 순서대로 연결해주면 되는 문제였음
 * 이렇게 했더니 시간 초과가남....
 */

// #include <iostream>
// #include <vector>
// #include <string>
// using namespace std;

// int N;
// vector<string> names;
// vector<vector<int>> tree;
// vector<bool> visited;

// string dfs(int cur) {
//     string result = names[cur];
//     for (int next : tree[cur]) {
//         result += dfs(next);
//     }
//     return result;
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(0);

//     cin >> N;
//     names.resize(N + 1);
//     tree.resize(N + 1);
//     visited.resize(N + 1, false);

//     for (int i = 1; i <= N; i++) {
//         cin >> names[i];
//     }

//     for (int i = 0; i < N - 1; i++) {
//         int a, b;
//         cin >> a >> b;
//         tree[a].push_back(b); // a에 b를 붙인다
//         visited[b] = true;    // b는 자식이므로 루트가 아님
//     }

//     // 루트 노드 찾기 (visited되지 않은 노드가 루트)
//     int root = 0;
//     for (int i = 1; i <= N; i++) {
//         if (!visited[i]) {
//             root = i;
//             break;
//         }
//     }

//     cout << dfs(root) << '\n';
//     return 0;
// }
/** 2트
 * 보완이 필요한 부분이
 * 아마 문자열 복사하는것에서 코스트가 많이 드는 것 같음
 * 문자열을 string이 아니라 char로 다뤄주면서 복사 하는 코스트를 줄여줄거임
 * 루트를 찾고 그 루트부터 시작해서 dfs 알고리즘을 따라갈거임 근데 처음 루트에서 진행된 다음 노드에 학교 이름을
 * result에 char로 받아 놓음으로써 문자열 복사시간을 줄여주는 것임
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int N;
vector<string> names;
vector<vector<int>> tree;
vector<bool> visited;

void dfs(int cur, vector<char>& result) {
    //cout << "현재 노드 " << cur << ": " << names[cur] << "\n";

    for (char c : names[cur]) {
        result.push_back(c);// 결과 배열에 계속 문자 하나씩 담아서 최종 결과를 담음
        //cout<<"result 배열에 들어간 학교:"<<c<<" \n";
    }

    for (int next : tree[cur]) {
        // cout << "처음 학교" << cur << " 나중학교 " << next << "\n";
        dfs(next, result);
    }

    // cout << "결과 노드" << cur << "\n";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N;
    names.resize(N + 1);
    tree.resize(N + 1);
    visited.resize(N + 1, false);

    for (int i = 1; i <= N; i++) {
        cin >> names[i];
    }

    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b); // a에 b를 붙인다
        visited[b] = true;    // b는 자식이므로 루트가 아님
    }

    // 루트 노드 찾기 (visited되지 않은 노드가 루트)
    int root = 0;
    for (int i = 1; i <= N; i++) {
        if (!visited[i]) {
            root = i;
            break;
        }
    }
    vector<char> result;

    dfs(root,result);
    for (char c : result) cout << c;
        cout << '\n';

    return 0;
}
