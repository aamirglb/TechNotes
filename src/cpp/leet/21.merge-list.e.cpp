// You are given the heads of two sorted linked lists list1 and list2.
// Merge the two lists in a one sorted list. The list should be made by splicing together the nodes of the first two lists.

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

//    t   f
//    1-   3  5  7  9
//      |
//    t   s
//    1   2  3  4  6
//
//

void updateLinks(ListNode* &result, ListNode* &head, ListNode* &list) {
    if(result) {
        result->next = list;
        result = list;
    } else {
        head = list;
        result = list;
    }
    list = list->next;
}

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {

    ListNode *result {};
    ListNode *head {};

    while(list1 && list2) {
        if(list1->val <= list2->val) {
            updateLinks(result, head, list1);
            // if(result) {
            //     result->next = list1;
            //     result = list1;
            // } else {
            //     head = list1;
            //     result = list1;
            // }
            // list1 = list1->next;
        } else {
            updateLinks(result, head, list2);
            // if(result) {
            //     result->next = list2;
            //     result = list2;
            // } else {
            //     head = list2;
            //     result = list2;
            // }
            // list2 = list2->next;
        }
    }
    if(list1) {
        if(result) result->next = list1;
        else head = list1;
    }
    if(list2) {
        if(result) result->next = list2;
        else head = list2;
    }

    return head;
}

int main()
{
    ListNode *first {};
    insertAtTail(first, {2, 4, 6, 8, 10});
    // display(first);

    ListNode *second {};
    insertAtTail(second, {1, 2, 3, 5, 7, 9, 11});
    // insertAtTail(second, {0});
    // display(second);

    ListNode *third = mergeTwoLists(first, second);
    display(third);
    // std::cout << "done.\n";
}