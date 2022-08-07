// Given the head of a singly linked list, sort the list using insertion sort, and return the sorted list's head.

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

ListNode* insertionSortList(ListNode* head) {

    if(!head || !head->next) return head;

    ListNode *result {nullptr};

    ListNode *tmp = head;
    while(tmp) {
        if(!result) {
            result = new ListNode(tmp->val);
        } else {
            if(tmp->val <= result->val) {
                insertAtHead(result, tmp->val);
            } else {
                ListNode *prev {nullptr};
                ListNode *curr = result;
                while(curr && curr->val <= tmp->val) {
                    prev = curr;
                    curr = curr->next;
                }
                ListNode *newNode = new ListNode(tmp->val);
                prev->next = newNode;
                newNode->next = curr;
            }
        }
        tmp = tmp->next;
    }
    return result;
}

int main()
{
    cout << "TC-1\n";
    ListNode *first {};
    insertAtTail(first, {4, 2, 1, 10, 3, 5});
    display(first);
    first = insertionSortList(first);
    display(first);

    cout << "TC-2\n";
    ListNode *second {};
    insertAtTail(second, {-1, 5, 3, 4, 0});
    display(second);
    second = insertionSortList(second);
    display(second);

    cout << "TC-3\n";
    ListNode *third {};
    insertAtTail(third, {1,1});
    display(third);
    third = insertionSortList(third);
    display(third);

    cout << "TC-4\n";
    ListNode *four {};
    insertAtTail(four, {1,1, 2, 4, 3, 5, 5});
    display(four);
    four = insertionSortList(four);
    display(four);
}