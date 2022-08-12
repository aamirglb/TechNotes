
#include <iostream>
#include <random>

using namespace std;

int guess(int num) {
    static random_device d;
    static default_random_engine e(d());
    static uniform_int_distribution<int> dist(0, 101);
    static int n = dist(e);

    cout << "Number to guess: " << n << endl;
    if(num == n) return 0;
    if(num < n) return 1;
    if(num > n) return -1;
}

int guessNumber(int n) {
    int low = 1;
    int high = n;
    int mid;
    int pick;

    do {
        mid = (low + high) / 2;
        cout << "you picked: " << mid << endl;
        pick = guess(mid);
        cout << "guess returned: " << pick << endl;
        // -1: mid is higher than guess
        if(pick < 0) {
            high = mid - 1;

        } else {
            low = mid+1;
        }
        // char ch; cout << "press space...\n";
        // cin >> ch;
    } while(pick != 0);
    return mid;
}

int main() {
    guessNumber(100);
}