#include <iostream>

using namespace std;

int z,o;

int fibonacci(int n) {
    if (n == 0) {
        
        z++;
        return 0;
    } else if (n == 1) {
        
        o++;
        return 1;
    } else {
        
        return fibonacci(n-1)+fibonacci(n-2);
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        int N;
        cin>>N;
        z=0;
        o=0;
        fibonacci(N);
        cout<<z<<" "<<o<<"\n";
    }
    return 0;
}