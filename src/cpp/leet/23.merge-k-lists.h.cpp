// You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.
// Merge all the linked-lists into one sorted linked-list and return it.

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

ListNode* mergeKLists(vector<ListNode*>& lists) {
    ListNode *result {nullptr};
    ListNode *head{nullptr};

    if(lists.size() == 0) return nullptr;

    // if we have an empty list
    // if(!lists[0]) return nullptr;

    if(lists.size() == 1) return lists[0];

    for(size_t i = 1; i < lists.size(); ++i) {
        ListNode *first = head;
        ListNode *second = lists[i];

        if(head) first = head;
        else first = lists[0];

        head = nullptr;
        result = nullptr;
        if(!first) cout << "first null\n";
        if(!second) cout << "second null\n";

        while(first && second) {
            if(first->val <= second->val) {
                if(result) {
                    result->next = first;
                    result = first;
                } else {
                    head = first;
                    result = first;
                }
                first = first->next;
            } else {
                if(result) {
                    result->next = second;
                    result = second;
                } else {
                    head = second;
                    result = second;
                }
                second = second->next;
            }
        }
        // merge remaining elements
        if(first) {
            if(result) result->next = first;
            else head = first;
        }
        if(second) {
            if(result) result->next = second;
            else head = second;
        }

    }
    return head;
}

int main()
{
    // ListNode *first {};
    // insertAtTail(first, {1, 4, 5});
    // display(first);

    // ListNode *second {};
    // insertAtTail(second, {1, 3, 4});
    // display(second);

    // ListNode *third {};
    // insertAtTail(third, {0, 2, 4});
    // display(third);

    // vector<ListNode *> lists {
    //     first,
    //     second,
    //     third,
    // };

    // auto m = mergeKLists(lists);
    // cout << "merged: \n";
    // display(m);

    ListNode *first{nullptr};
    ListNode *second{};
    insertAtTail(second, {1});
    vector<ListNode *> lists {
        first,
        second,
    };
    auto m = mergeKLists(lists);
    cout << "merged: \n";
    display(m);

}