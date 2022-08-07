// Given the head of a sorted linked list, delete all duplicates such that each element appears only once. Return the linked list sorted as well.
#include <iostream>
#include <vector>

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

ListNode* deleteDuplicates(ListNode* head) {
    if(!head || !head->next) return head;

    ListNode *tmp = head;

    while(tmp && tmp->next) {
        if(tmp->val == tmp->next->val) {
            auto t = tmp->next;
            tmp->next = tmp->next->next;
            delete t;
            continue;
        }
        tmp = tmp->next;
    }
    return head;
}

int main()
{
    cout << "TC-1\n";
    ListNode *first {};
    insertAtTail(first, {1, 1, 1, 3, 3, 3, 3, 3, 3, 5});
    display(first);
    first = deleteDuplicates(first);
    display(first);
}