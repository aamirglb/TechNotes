#include<iostream>
#include<vector>
using namespace std;

// prints vector
void print(vector<int> result){
    if(result.empty()){
        cout << "NULL" << endl;
    }
    else{
        for(int i:result){
            cout << i << ", ";
        }
        cout << endl;
    }
}

vector<int> best_sum(int target_value, vector<int> vec){
    // base case
    if(target_value==0) return {target_value};

    if(target_value < 0) return {};
    vector<int> shortest = {}; // for best and shortest combination
    for(int i : vec){
        int reminder = target_value - i;
        // every combination will be stored in temp_combination
        vector<int> temp_combination = best_sum(reminder,vec);
        // checking if there is any combinations availabel or not?
        if(!temp_combination.empty()){
            temp_combination.push_back(i);
            // for getting shortest possible combination
            if(shortest.empty() || shortest.size()>temp_combination.size()){
                shortest = temp_combination;
            }
        }
    }
    return shortest;
}
int main(){
    vector<int> shortest;
    shortest = best_sum(25,{1,5,10});
    // shortest.erase(shortest.begin());
    print(shortest);
    shortest = best_sum(32,{1,5,10});
    // shortest.erase(shortest.begin());
    print(shortest);
    return 0;
}