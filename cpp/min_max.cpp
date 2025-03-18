#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

string solution(string s) {
    vector<int> numbers;
    stringstream ss(s);
    string temp;

    while(ss>>temp){
        numbers.push_back(stoi(temp));
    }

    int min=*min_element(numbers.begin(),numbers.end());
    int max=*max_element(numbers.begin(),numbers.end());

    
    return to_string(min)+" "+to_string(max);
}

int main(){
    cout << solution("1 2 3 4");
}