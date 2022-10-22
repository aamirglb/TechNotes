#include <bits/stdc++.h>

// Sleep for one minutes
int main() {
    using namespace std;
    using namespace std::chrono;
    using namespace std::chrono_literals;
    auto start_ctime = system_clock::now()/60*60+10;//beginning second of next minute
    auto until= chrono::system_clock::from_time_t(start_ctime);
    for(;;until+=60s){
        this_thread::sleep_until(until);
        auto diff=system_clock::now() - start_ctime;
        cout << diff << endl;
    }
}