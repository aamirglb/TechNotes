// Given the head of a singly linked list, reverse the list, and return the reversed list.

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

void display(ListNode *head) {
    ListNode *tmp = head;
    if(!head) return;

    while(tmp->next) {
        cout << tmp->val << " -> ";
        tmp = tmp->next;
    }
    cout << tmp->val << endl;
}

ListNode* reverseList(ListNode* head) {

    if(!head || !head->next) return head;

    ListNode *prev{nullptr};
    ListNode *curr{nullptr};
    ListNode *nxt{head};

    while(nxt) {
        prev = curr;
        curr = nxt;
        nxt = nxt->next;
        curr->next = prev;
    }
    return curr;
}

int main() {
    ListNode *first {nullptr};
    insertAtTail(first, {1, 2, 3, 4, 5});
    display(first);
    first = reverseList(first);
    display(first);

    ListNode *second {nullptr};
    insertAtTail(second, {1});
    display(second);
    second = reverseList(second);
    display(second);
}