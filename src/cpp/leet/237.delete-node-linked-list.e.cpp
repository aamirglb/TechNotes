// Write a function to delete a node in a singly-linked list. You will not be given access to the head of the list, instead you will be given access to the node to be deleted directly.
// It is guaranteed that the node to be deleted is not a tail node in the list.

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

void deleteNode(ListNode* node) {
    ListNode *tmp = node->next;

    if(!node->next) {
        delete node;
        return;
    }
    node->val = node->next->val;
    node->next = node->next->next;
    delete tmp;
}

int main() {
    ListNode *node{nullptr};

    ListNode *f {nullptr};
    insertAtTail(f, {1, 2, 3, 4, 5});
    node = f->next->next;  // pointing to 3
    display(f);
    deleteNode(node);
    display(f);

    node = f;
    deleteNode(node);
    display(f);

}