// Implement first in first out (FIFO) queue using only two stacks.

#include <iostream>
#include <stack>
using namespace std;

class MyQueue {
public:
    stack<int> primary;
    stack<int> secondary;

    MyQueue() {
    }

    void push(int x) {
        primary.push(x);
    }

    int pop() {
        if(secondary.empty()) {
            // transfer elements from primary
            while(!primary.empty()) {
                secondary.push(primary.top());
                primary.pop();
            }
        }
        int ele = secondary.top();
        secondary.pop();
        return ele;
    }

    int peek() {
        if(secondary.empty()) {
            // transfer elements from primary
            while(!primary.empty()) {
                secondary.push(primary.top());
                primary.pop();
            }
        }
        return secondary.top();
    }

    bool empty() {
        if(primary.empty() && secondary.empty()) return true;
        else return false;
    }
};

int main() {
    MyQueue q; // = new MyQueue();
    q.push(1);
    q.push(2);
    cout << q.peek() << endl;
    q.pop();
    cout << boolalpha << q.empty() << endl;
}