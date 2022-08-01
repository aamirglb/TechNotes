// Given a linked list, swap every two adjacent nodes and return its head. You must solve the problem without modifying the values in the list's nodes (i.e., only nodes themselves may be changed.)

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

ListNode* swapPairs(ListNode* head) {
    if(!head || !head->next) return head;
    // if(!head->next) return head;

    ListNode* dummy = new ListNode(-1, head);

    ListNode* curr = head;
    ListNode* prev = dummy;

    while(curr && curr->next) {
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

    first = swapPairs(first);
    display(first);

    ListNode *second{};
    insertAtTail(second, {10});
    display(second);
    second = swapPairs(second);
    display(second);
}