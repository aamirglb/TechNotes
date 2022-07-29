// Given the head of a linked list, remove the nth node from the end of the list and return its head.

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

void display(ListNode *head) {
    ListNode *tmp = head;
    if(!head) return;

    while(tmp->next) {
        cout << tmp->val << " -> ";
        tmp = tmp->next;
    }
    cout << tmp->val << endl;
}

ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode *dummy = new ListNode(-1, head);

    ListNode* prev {dummy};
    ListNode* curr {head};
    while(n-- > 0 && curr) curr = curr->next;

    // Now the offset between prev and curr is n nodes
    // move both pointers now till curr becomes null
    while(curr) {
        curr = curr->next;
        prev = prev->next;
    }

    ListNode* tmp = prev->next;
    prev->next = prev->next->next;
    delete tmp;
    return dummy->next;
}

// ListNode* removeNthFromEnd(ListNode* head, int n) {
//     ListNode* tmp = head;
//     int totalNodes {};
//     while(tmp) {
//         ++totalNodes;
//         tmp = tmp->next;
//     }

//     ListNode* prev {nullptr};
//     ListNode* curr {head};
//     int target = totalNodes - n; // 5 - 2 = 3
//     while(target > 0) {
//         prev = curr;
//         curr = curr->next;
//         --target;
//     }
//     if(n == totalNodes) {
//         head = head->next;
//     } else if(n == 1) {
//         prev->next = nullptr;
//         delete curr;
//     } else {
//         prev->next = curr->next;
//         delete curr;
//     }
//     return head;
// }

int main()
{
    cout << "TC-1\n";
    ListNode *first {};
    insertAtTail(first, {1, 2, 3, 4, 5});
    display(first);
    first = removeNthFromEnd(first, 2);
    display(first);

    cout << "\nTC-2\n";
    ListNode* second{};
    insertAtTail(second, {1});
    display(second);
    second = removeNthFromEnd(second, 1);
    display(second);
    // first = removeNthFromEnd(first, 5);

    cout << "\nTC-3\n";
    display(first);
    first = removeNthFromEnd(first, 4);
    display(first);
}

