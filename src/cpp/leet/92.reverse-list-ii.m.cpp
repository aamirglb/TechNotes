// Given the head of a singly linked list and two integers left and right where left <= right,
// reverse the nodes of the list from position left to position right, and return the reversed list.

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
    while(tmp->next) {
        cout << tmp->val << " -> ";
        tmp = tmp->next;
    }
    cout << tmp->val << endl;
}

// Reverse link list upto k nodes and return previous and current head of rotated list
pair<ListNode*, ListNode *> reverseLinkList(ListNode* head, int left, int right) {
    ListNode *prev {nullptr};
    ListNode *curr {nullptr};
    ListNode *next {head};
    ListNode *prevHead = head;

    while(left <= right) {
        prev = curr;
        curr = next;
        next = next->next;
        curr->next = prev;
        ++left;
    }
    // cout << "** Reversed list with k = " << n << endl;
    // display(curr);
    return make_pair(prevHead, curr);
}

ListNode* reverseBetween(ListNode* head, int left, int right) {

    if(!head || !head->next) return head;
    if(left == right) return head;

    ListNode *start {head};
    ListNode *end {head};
    ListNode *beforeStart {};
    ListNode *afterEnd {};

    int l {1}, r {1};

    while(l < left && start) {
        beforeStart = start;
        start = start->next;
        ++l;
    }

    while(r < right && end) {
        end = end->next;
        if(end) afterEnd = end->next;
        r++;
    }

    auto [prev, curr] = reverseLinkList(start, left, right);
    cout << "Reversed List: ";
    display(curr);

    if(beforeStart) {
        beforeStart->next = curr;
    }
    if(afterEnd) {
        prev->next = afterEnd;
    }

    if(left == 1) return curr;
    else return head;
}

int main() {
    ListNode *head {nullptr};
    insertAtTail(head, {3, 5});

    auto tmp = reverseBetween(head, 1, 1);
    cout << "Final list: ";
    display(tmp);

    // ListNode *sec {nullptr};
    // insertAtTail(sec, {1, 2, 3, 4, 5});

    // tmp = reverseBetween(sec, 2, 4);
    // cout << "Final list: ";
    // display(tmp);
}
