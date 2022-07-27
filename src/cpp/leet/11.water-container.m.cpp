//

#include <iostream>
#include <vector>

using namespace std;

// Brute force solution
int maxAreaBf(vector<int>& height) {
    int result = 0;

    for(size_t i = 0; i < height.size(); ++i) {
        for(size_t j = i + 1; j < height.size(); ++j) {
            // find the minimum between i and j
            int minHeight = min(height[i], height[j]);
            int area = minHeight * (j - i);
            result = max(result, area);
        }
    }
    return result;
}

int maxArea(vector<int>& height) {
    int ans = 0;

    size_t i = 0;
    size_t j = height.size() - 1;

    while(i < j) {
        int area = (j - i) * min(height[i], height[j]);
        cout << "a : " << area << endl;
        ans = max(area, ans);
        if(height[i] < height[j]) ++i;
        else --j;
    }
    return ans;
    // for(size_t i = 0; i < height.size(); ++i) {
    //     for(size_t j = height.size() -1; i >= i; ++j) {

    //     }
    // }
}

int main()
{
    vector<int> h {
        1,8,6,2,5,4,8,3,7
    };

    cout << "max area: " << maxArea(h) << endl;
}