#include <iostream>
#include <numeric>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// void test()
// {
//     int n = 7, k = 2;
//     int a[] = {1, 7, 4, 3, 4, 8, 7};

//     map<int, int> m;
//     for(int i=0; i<n; ++i) {
//         ++m[a[i]];
//         int c = count(m.begin(), m.end(), a[i]);
//     }

//     // vector<int> count(n, 0);
//     // for(int i=0; i<n; ++i) {
//     //     for(int j=0; j<n; ++j) {
//     //         // count
//     //         if(a[i] == a[j]) ++count[i];
//     //     }
//     // }
//     // for(const auto& e : count) std::cout << e << '\n';
// }

int equilibriumPoint(long long a[], int n) {

        if(n==1) return 1;

        for (int i = 1; i < n; i++)
        {
            a[i] += a[i - 1];
            cout << a[i] << " ";
        } cout << endl;

        for (int i = 0; i < n; i++)
        {
            if (a[i] == (a[n - 1] - a[i + 1]))
                return i + 1 + 1;
        }

        // long long sumLeft = 0, sumRight = 0;

        // for(int i=0; i<n-2; ++i)
        // {
        //     sumLeft += a[i];
        //     cout << "LeftSum = " << sumLeft << endl;

        //     sumRight = 0;
        //     for(int j=i+2; j<n; ++j)
        //     {
        //         sumRight += a[j];
        //         cout << "RightSum = " << sumRight << endl;
        //         if(sumRight > sumLeft) break;
        //         if(sumLeft == sumRight && j == n - 1)
        //         {
        //             cout << "== " << sumLeft << " " << sumRight << endl;
        //             return i+2;
        //         }
        //     }
        // }
        return -1;
}

int main()
{
    // std::vector<int32_t> v {6,1,2,8,3,4,7,10,5};
    // int32_t n = 10;

    // int32_t sum = (n * (n+1))/2;
    // int32_t sum2 = std::accumulate(v.begin(), v.end(), 0);
    // std::cout << sum - sum2 << std::endl;
    // test();

    vector<int> v2 {3, 4, 8, 2, 4};
    sort(v2.begin(), v2.end(), greater<int>());
    for(const auto& e : v2) std::cout << e << " ";

    long long a[]= {27, 4, 25, 6, 6, 1, 27, 22, 19, 29, 6, 9, 36, 24, 6, 15, 5};
    // std::cout << equilibriumPoint(a, 17);

    long long b[] = {1,3,5,2,2};
    std::cout << equilibriumPoint(b, 5);
}
