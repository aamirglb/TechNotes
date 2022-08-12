// Given the head of a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x.
// You should preserve the original relative order of the nodes in each of the two partitions.

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

void insertAtTail(ListNode* &head, int data) {
    ListNode *tmp = new ListNode(data);
    if(head == nullptr) {
        head = tmp;
    } else {
        ListNode *t = head;
        while(t->next != nullptr) t = t->next;
        t->next = tmp;
    }
}

void display(ListNode* &head) {
    ListNode *curr = head;
    while(curr->next != nullptr) {
        std::cout << curr->val << " -> ";
        curr = curr->next;
    }
    std::cout << curr->val << std::endl;
}

ListNode* partition(ListNode* head, int x) {
    if(!head || !head->next) return head;

    vector<int> left, right;
    ListNode *tmp {head};

    while(tmp) {
        if(tmp->val < x) left.push_back(tmp->val);
        else right.push_back(tmp->val);
        tmp = tmp->next;
    }
    tmp = head;
    for(const auto& e : left) { tmp->val = e; tmp = tmp->next; }
    for(const auto& e: right) { tmp->val = e; tmp = tmp->next; }
    return head;
    // ListNode *left = new ListNode(-1);
    // ListNode *right = new ListNode(-1);

    // ListNode *tmp {head};

    // while(tmp) {
    //     if(tmp->val < x) {
    //         left->next = tmp;
    //     } else {
    //         right->next = tmp;
    //     }
    //     tmp = tmp->next;
    // }

    // tmp = left;
    // while(tmp->next) tmp = tmp->next;
    // tmp->next = right;
    // return left;
}

int main() {
    cout << "TC-1: \n";
    ListNode* h1 {nullptr};
    for(auto &val : {1, 4, 3, 2, 5, 2}) insertAtTail(h1, val);
    display(h1);
    h1 = partition(h1, 3);
    display(h1);
}