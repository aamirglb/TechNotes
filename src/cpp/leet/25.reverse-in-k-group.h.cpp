// Given the head of a linked list, reverse the nodes of the list k at a time, and return the modified list.

#include <iostream>
#include <vector>
#include <initializer_list>

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
        if(head)
        {
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

void display(ListNode *head) {
    ListNode *tmp = head;
    while(tmp->next) {
        cout << tmp->val << " -> ";
        tmp = tmp->next;
    }
    cout << tmp->val << endl;
}

ListNode* reverseKGroup(ListNode* head, int k) {

    if(!head || !head->next) return head;
    // if(!head->next) return head;

    ListNode* dummy = new ListNode(-1, head);

    ListNode* curr = head;
    ListNode* prev = dummy;

    while(curr && curr->next) {
        auto n = k;
        auto tmp = curr;
        while(n) {
            --n;
            tmp = tmp->next;
            if(!tmp) break;
        }
        // continue since we have enough nodes in the list
        if(n == 0) {

        }

        // save pointer
        ListNode *nextPair = curr->next->next;
        ListNode *second = curr->next;

        // swap links of curr and second
        second->next = curr;
        curr->next = nextPair;
        // IMP!!
        prev->next = second;

        // update pointers for next iteration
        prev = curr;
        curr = nextPair;
    }

    return dummy->next;
}

int main()
{
    ListNode *first {};
    insertAtTail(first, {1, 2, 3, 4, 5, 6});
    display(first);


}