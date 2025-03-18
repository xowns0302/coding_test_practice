#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;

int solution(vector<int> A, vector<int> B){
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());
    
    int ans=0;
    for(int i=0;i<A.size();i++){
        ans+=A[i]*B[(A.size()-1)-i];
    }
    
    return ans;
}

int main(){
    cout<<solution({1,4,2},{5,4,4});
}//여기까지가 내가 생각한 코드

//여기는 더 간단한 코드 
//rbegin, rend를 사용하면 내림차순으러 정렬할 수있음
//innerproduct는 헤더 numeric에 포함된거 
//inner_product(첫 번째 배열 시작, 첫 번째 배열 끝, 두 번째 배열 시작, 초기값);
//변수는 이렇게 넣으면 두 배열의 값을 곱해서 각각 곱한 수의 합을 리턴함
// #include <vector>
// #include <numeric>
// #include <algorithm>
// using namespace std;
// int solution(vector<int> A, vector<int> B){
//     sort(A.begin(),A.end());  sort(B.rbegin(),B.rend());
//     return inner_product(A.begin(),A.end(),B.begin(),0);
// }