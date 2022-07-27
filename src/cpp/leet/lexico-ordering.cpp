#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <list>
#include <stack>
#include <numeric>
#include <map>

using namespace std;

void reverse(string &S, int i, int j)
{
    std::cout << i << " " << j << std::endl;
    while (i < j)
    {
        S[i++] = S[j--];
    }
}

template <typename T>
void print(const T &v, string sep=" ")
{
    for(const auto& e : v) cout << e << sep;
    cout << '\n';
}

// void print(const vector<int32_t> &v)
// {
//     for(const auto& e : v) cout << e << ' ';
//     cout << '\n';
// }

/*
For Input:
ljr

Your Code's output is:
ljr lrj rjl rlj

It's Correct output is:
jlr jrl ljr lrj rjl rlj
*/

int main()
{
    vector<string> result;
    string S = "ljr";
    // vector<int32_t> S {0, 1, 2};

    // Find the largest i such that P[i]<P[i+1].
    // (If there is no such x, P is the last permutation.)

    // sort in alphabitical order
    sort(S.begin(), S.end());

    // Implement the algorithm from here
    // https://www.quora.com/How-would-you-explain-an-algorithm-that-generates-permutations-using-lexicographic-ordering
    while(true) {
        result.push_back(S);
        int x = -1;
        for(size_t i = 0; i < S.size() - 1; ++i) {
            if(S[i] < S[i+1]) x = i;
        }

        if(x == -1) {
            break;
        }

        int32_t y = -1;
        for(size_t j = 0; j < S.size(); ++j) {
            if(S[x] < S[j]) y = j;
        }

        swap(S[x], S[y]);

        reverse(S.begin()+x+1, S.end());
    }

    int32_t i = 0;
    for(const auto& s: result) {
        std::cout << ++i << ". " << s << std::endl;
    }

if(0) {
    // reverse words
    string s = "i.like.this.program.very.much";
    stringstream ss(s);
    string t;
    // stack<string> stk;
    list<string> lst;

    while(getline(ss, t, '.')){
        lst.push_front(t);
        lst.push_front(".");
    }

    lst.erase(lst.begin());
    string r = accumulate(lst.begin(), lst.end(), string(""));
    cout << r;
    // list<string>::iterator itr = lst.begin();
    // for(int i=0; i < lst.size() - 1; ++i) ++itr;
    // lst.erase(lst.begin());

    // print(lst, "");
    // string r(lst.begin(), lst.end());
    // cout << r;
}

if(1) {
    // string S="geeksforgeeks";
    string S="okmnijnhbtgv";
    map<char, int> m;
    size_t start = 0;
    string longest, tmp;
    for(size_t i = 0; i < S.size(); ++i) {
        m[ S[i] ]++;

        for(const auto& [k,v] : m) cout << k << " : " << v << endl;
        cout << "----\n";
        if(m[ S[i] ] > 1) {

            if(tmp.size() > longest.size()) {
                cout << tmp << endl;
                longest = tmp;
            }
            tmp.clear();
            m.clear();
            // leave char till first duplicate
            size_t j;
            for(j = start; S[j] != S[i]; ++j);
            ++j;
            start = j;
            cout << "coping left overs: ";
            for(size_t k = j; k <= i; ++k)
            {
                cout << S[k];
                m[ S[k] ]++;
                tmp.push_back(S[k]);
            }
            cout << endl;
        } else {
            tmp.push_back(S[i]);
            if(i == S.size() - 1 && tmp.size() > longest.size()) longest = tmp;
        }
    }
    if(longest.size() == 0) longest = tmp;
    cout << longest << " : " << longest.size() << std::endl;
}
}