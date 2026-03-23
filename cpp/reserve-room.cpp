/**
 * 주요전제 
 * 회의실은 9시~18시 까지만 이용가능
 */

#include <iostream>
#include <array>
#include <string>
#include <map>


using namespace std;

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin>> n >> m;
    map<string,array<int,9>>room;

    for(int i=0;i<n;i++){
        string a;
        cin>>a;
        room[a].fill(0);
    }
    for(int i=0;i<m;i++){
        string a;
        int start, end;
        cin >> a>>start>>end;
        for(int j=start;j<end;j++){
            room[a][j-9]=1;
        }
    }
    bool first =true;
    for(auto& [name,slots]:room){
        if(!first) cout << "-----\n";
        first = false; 
        cout<<"Room "<<name <<":\n";
        int i=0;
        int j=0;
        int count=0;
        while(j<9){
            if(slots[j]==0){
                count++;
                while(j<9&&slots[j]==0)j++;
            }else{
                j++;
            }
        }
        if(count==0){
            cout<<"Not available\n";
        }else{
            cout<<count<<" available:\n";
            while(i<9){
                if(slots[i]==0){
                    int s= i+9;
                    while(i<9 &&slots[i]==0)i++;
                    int e = i+9;                           
                    if(s < 10) cout << "0";                              
                    cout << s << "-";                                    
                    if(e < 10) cout << "0";                              
                    cout << e << "\n";
                    if(!count--)return 0;
                }else i++;
            }
        }
    }

    return 0;
}