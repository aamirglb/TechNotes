// #include <iostream>

// // Using Pascal's Triangle, solve combination formula

// int32_t nCr(int32_t n, int32_t r)
// {
//     if(r==0 || r==n) return 1;
//     return nCr(n-1, r-1) + nCr(n-1, r);
// }

// int main(int argc, char *argv[])
// {
//     std::cout << nCr(4, 2) << std::endl;
// }

#include <iostream>
#include <string>
#include <vector>
#include <functional>

using namespace std;
void split(const string &s, char c, vector<string> &v)
{
    string::size_type i = 0;
    string::size_type j = s.find(c);

    while (j != string::npos)
    {
        std::cout << "*** " << s.substr(i, j - i) << std::endl;
        v.push_back(s.substr(i, j - i));
        i = ++j;
        j = s.find(c, j);

        if (j == string::npos)
        {
            v.push_back(s.substr(i, s.length()));
        }
    }
}

int main()
{
    // Fill the code here
    //  Strings
    string prompt1 = "Enter name: ";
    string prompt2 = "Enter roll number: ";
    string prompt3 = "Enter Date of Birth [DD MM YY] format: ";

    vector<string> v;
    string s = "Something To Put Here";

    split(s, ' ', v);

    for (int i = 0; i < v.size(); ++i)
    {
        cout << "### " << v[i] << endl;
    }

    return 0;
}