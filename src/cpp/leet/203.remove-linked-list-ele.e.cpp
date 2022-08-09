// Given the head of a linked list and an integer val, remove all the nodes of the linked list that
// has Node.val == val, and return the new head.

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
    if(!head) {
        cout << "null" << endl;
        return;
    }

    while(tmp->next) {
        cout << tmp->val << " -> ";
        tmp = tmp->next;
    }
    cout << tmp->val << endl;
}

ListNode* removeElements(ListNode* head, int val) {
    if(!head) return nullptr;
    ListNode *newNode {head};
    ListNode *tmp {nullptr};

    while(head && head->val == val) {
        tmp = head;
        newNode = head->next;
        head = head->next;
        delete tmp;
    }
    ListNode *curr {head};
    ListNode *prev {nullptr};

    while(curr) {
        if(curr->val == val) {
            ListNode *tmp = curr;
            prev->next = curr->next;
            curr = curr->next;
            delete tmp;
            continue;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    return newNode;
}

int main() {
    ListNode *f {nullptr};
    insertAtTail(f, {1, 1, 2, 3, 1, 5, 6, 1});
    display(f);
    f = removeElements(f, 1);
    display(f);

    ListNode *s {nullptr};
    insertAtTail(s, {10, 1, 2});
    display(s);
    s = removeElements(s, 10);
    display(s);
}