/** #16953번 A->B 
 * 이 문제는 A가 B로 바꾸는데 필요한 연산횟수의 최솟값을 찾는 문제
 * 연산은 곱하기 2와 수의 가장 오른 쪽에 1을 붙이는 것 뿐임
 * 이거를 트리로 표현하면 
 * queue에 담으면서 그냥 depth 만 따로 기록해서 적어주면 됨
 * 처음 시작이 depth가 1이면 이 자식들을 queue에 담을땐 ++ 해서
 * 담아주기, 뎁스는 복제 배열하나만들어서 기록해줘도 될듯?
 * 
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int bfs(long long A, long long B){
    queue<long long> q;
    q.push(A);
    long long depth=1;
    
    while(!q.empty()){
        int sz=q.size();

        while(sz--){
            long long x=q.front();
            q.pop();
            if (x==B) return depth;
            if (x<=B/2) q.push(x*2);
            if (x<=(B-1)/10) q.push(x*10 +1);
        }
        ++depth;
    }
    return -1;

}

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int A,B;
    cin>>A>>B;
    
    int result=bfs(A,B);
    cout<< result<<"\n";

    return 0;
}