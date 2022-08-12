// Given the head of a sorted linked list, delete all nodes that have duplicate numbers, leaving
// only distinct numbers from the original list. Return the linked list sorted as well.

#include <iostream>
#include <vector>
#include <set>

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

ListNode* deleteDuplicates(ListNode* head) {
    if(!head || !head->next) return head;
    ListNode *dummy = new ListNode(-1, head);
    set<int> nodesToDelete;

    ListNode *tmp {head};
    while(tmp->next) {
        if(tmp->val == tmp->next->val)
            nodesToDelete.insert(tmp->val);
        tmp = tmp->next;
    }

    if(nodesToDelete.empty()) return head;
    for(const auto& e: nodesToDelete) cout << e << ' ';
    cout << endl;

    ListNode *curr {head};
    ListNode *prev {dummy};

    while(curr) {
        if(nodesToDelete.find(curr->val) != nodesToDelete.end()) {
            ListNode *tmp {curr};
            curr = curr->next;
            prev->next = curr;
            delete tmp;
            continue;
        }
        prev = curr;
        curr = curr->next;
    }
    return dummy->next;
}

int main() {
    ListNode *first {};
    insertAtTail(first, {1, 2, 3, 3, 4, 4, 5});
    display(first);
    first = deleteDuplicates(first);
    display(first);

    ListNode *s{nullptr};
    insertAtTail(s, {1, 1, 1, 2, 3});
    display(s);
    s = deleteDuplicates(s);
    display(s);
}