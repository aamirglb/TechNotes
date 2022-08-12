// Given the head of a linked list, rotate the list to the right by k places.

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

// Count number of nodes
int countNodes(ListNode *head) {
    int totalNodes {};
    while(head) {
        ++totalNodes;
        head = head->next;
    }
    return totalNodes;
}

// This function should be called with atleast 2 nodes
ListNode* rotateOnce(ListNode* head) {
    ListNode *curr {head};
    ListNode *prev {nullptr};

    // move to the last node while maintaining a tail pointer
    while(curr->next) {
        prev = curr;
        curr = curr->next;
    }

    // Point the last node to the first one
    curr->next = head;
    // Make last but one node as last node
    prev->next = nullptr;

    // return last node as current head
    return curr;
}

ListNode* rotateRight(ListNode* head, int k) {
    if(!head || !head->next || k == 0) return head;

    k = k % countNodes(head);
    for(int i = 0; i < k; ++i) {
        head = rotateOnce(head);
    }
    return head;
}

int main() {
    cout << "TC-1: k=4\n";
    ListNode* h1 {nullptr};
    for(auto &val : {1, 2, 3, 4, 5}) insertAtTail(h1, val);
    display(h1);
    h1 = rotateRight(h1, 4);
    display(h1);

    cout << "\nTC-2: k=4\n";
    ListNode *h2 {nullptr};
    for(auto &val : {0, 1, 2}) insertAtTail(h2, val);
    display(h2);
    h2 = rotateRight(h2, 4);
    display(h2);

    cout << "\nTC-3: k=3\n";
    ListNode *h3 {nullptr};
    for(auto &val : {1, 2}) insertAtTail(h3, val);
    display(h3);
    h3 = rotateRight(h3, 3);
    display(h3);

    cout << "\nTC-1: k=2000000000\n";
    ListNode *h4 {nullptr};
    for(auto &val : {1, 2, 3}) insertAtTail(h4, val);
    display(h4);
    h4 = rotateRight(h4, 2000000000);
    display(h4);
}

