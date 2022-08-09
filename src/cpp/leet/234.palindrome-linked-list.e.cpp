// Given the head of a singly linked list, return true if it is a palindrome.

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void insertAtTail(ListNode* &head, initializer_list<int32_t> values)
{
    for(const auto& value : values) {
        ListNode *newNode = new ListNode(value);
        if(head) {
            ListNode *tmp = head;
            while(tmp->next != nullptr) {
                tmp = tmp->next;
            }
            tmp->next = newNode;
        } else {
            head = newNode;
        }
    }
}

void insertAtHead(ListNode *&head, int32_t value) {
    ListNode *curr = new ListNode(value);

    if(!head) {
        head = curr;
    } else {
        curr->next = head;
        head = curr;
    }
}

bool isPalindrome(ListNode* head) {
    ListNode *rev {nullptr};
    ListNode *tmp = head;
    while(tmp) {
        insertAtHead(rev, tmp->val);
        tmp = tmp->next;
    }

    tmp = head;
    while(rev && tmp) {
        if(rev->val != tmp->val) return false;
        tmp = tmp->next;
        rev = rev->next;
    }
    return true;
}

int main() {
    ListNode *f {nullptr};
    insertAtTail(f, {1, 2, 2, 1});
    cout << boolalpha << isPalindrome(f) << endl;

    ListNode *s {nullptr};
    insertAtTail(s, {1, 2});
    cout << boolalpha << isPalindrome(s) << endl;
}