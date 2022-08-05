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

// Reverse link list upto k nodes and return previous and current head of rotated list
pair<ListNode*, ListNode *> reverseLinkList(ListNode* head, int k) {
    ListNode *prev {nullptr};
    ListNode *curr {nullptr};
    ListNode *next {head};
    ListNode *prevHead = head;

    while(k > 0) {
        prev = curr;
        curr = next;
        next = next->next;
        curr->next = prev;
        --k;
    }
    // cout << "** Reversed list with k = " << n << endl;
    // display(curr);
    return make_pair(prevHead, curr);
}

ListNode* reverseKGroup(ListNode* head, int k) {
    if(!head || !head->next) return head;

    ListNode *tmp = head;
    ListNode *newHead {nullptr};
    ListNode *lastNode {nullptr};
    int n = k;

    // check if there are enough nodes to proceed
    while(--n) {
        tmp = tmp->next;
        if(!tmp) return head;
    }
    tmp = head;
    while(tmp) {
        // tmp will always point to next kth node
        ListNode *nextKthNode = tmp;
        n = k;
        // move tmp to the next kth node
        while(--n >= 0 && tmp) {
            tmp = tmp->next;
        }

        // if enough nodes to continue
        if(n < 0) {
            auto [prev, curr] = reverseLinkList(nextKthNode, k);
            // set new node of modified list
            if(!newHead) newHead = curr;

            // maintain a pointer to the last node of the list, so that we can attach it to
            // next kth node
            if(!lastNode) {
                lastNode = prev;
            } else {
                lastNode->next = curr;
                lastNode = prev;
            }
        } else {
            // if there are any left out nodes, attach it to the tail
            lastNode->next = nextKthNode;
        }
    }
    return newHead;
}

int main()
{
    ListNode *first {};
    insertAtTail(first, {1, 2, 3, 4});
    display(first);

    auto newHead = reverseKGroup(first, 3);
    display(newHead);

}