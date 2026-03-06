/** #1389번 케빈 베이컨의 6단계 법칙
 * 각 사람이 모든 노드에 도착하는 최소 횟수를 구하여 다 더하기
 * 횟수를 비교하여 가장 케빈 베이컨 수가 작은 사람을 구하는 문제
 * bfs를 하나 구현해서 그래프 내에서 bfs를 사람 수 만큼 돌리고
 * 결과 값을 따로 저장해 계산하는 방법
 * 
 * 
 */
#include <iostream>
#include <vector>

using namespace std;


int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N,M;
    cin>>N>>M;
    vector<vector<int>>friends(N+1);

    for(int i=0;i<M;i++){
        int a,b;
        cin>>a>>b;
        friends[a].push_back(b);
        friends[b].push_back(a);
    }


    return 0;
}