#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

string FirstNonRepeating(string A)
{
    string res = "";
    queue<char> que;
    vector<int> hash(26, 0);

    for (auto ch : A) {
        hash[ch - 'a']++;

        if (hash[ch - 'a'] == 1)
            que.push(ch);

        while (!que.empty() && hash[que.front() - 'a'] != 1)
            que.pop();

        if (que.empty())
            res += '#';
        else
            res += que.front();
    }
    return res;
}

int main()
{
    string s = "aabcaabc";
    std::cout << FirstNonRepeating(s) << endl;
}