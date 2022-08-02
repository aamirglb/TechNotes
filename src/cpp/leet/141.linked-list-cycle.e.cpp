// Given head, the head of a linked list, determine if the linked list has a cycle in it.

#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

bool hasCycle(ListNode *head) {
    ListNode *slow = head;
    ListNode* fast = head;

    if(!head) return false;
    if(head->next) fast = fast->next;

    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast)
            return true;
    }
    return false;
}

