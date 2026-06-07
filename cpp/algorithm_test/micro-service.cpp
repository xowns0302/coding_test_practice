/** greedy같긴한데
 정렬해서 큰값부터 최대한 조합하고 300이 세개 이상이면 일단 300은 세개로 묶기 
 경우의수가 1개 짝 2개 짝 3개 짝 이렇게만 나옴
 3개짝은 300,300,300
 600이상일 경우는 항상 1개짝
 600이하이면서 301이상일경우는 2개 조합으로 들어가는 경우
 300이면 조합으로 들어갈지 아니면 3개로 묶일지
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;

    cin>>t;

    while(t--){
        vector<int>mic;
        int n;
        int result=0;
        int count_300=0;
        cin>>n;
        for(int j=0;j<n;j++){
            int m;
            cin>>m;
            if(m>600){
                result++;
            }else if(m==300){
                count_300++;
            }else{
                mic.push_back(m);
            }
        }
        sort(mic.begin(),mic.end());
        int left=0, right=(int)mic.size()-1;
        int S=0; // 혼자 남은 non-300 서버 수
        while(left<=right){
            if(left==right){ S++; break; }
            if(mic[left]+mic[right]<=900){
                result++;
                left++; right--;
            }else{
                S++; right--;
            }
        }
        result+=S;

        // 혼자 남은 non-300 서버에 300 흡수 (여유공간 >= 300 보장)
        int absorb=min(S, count_300);
        count_300-=absorb;

        // 남은 300들: 최대 3개씩 묶기
        result+=(count_300+2)/3;
        cout<<result<<"\n";
    }



    return 0;
}