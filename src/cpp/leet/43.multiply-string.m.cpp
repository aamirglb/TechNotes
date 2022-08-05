// Given two non-negative integers num1 and num2 represented as strings, return the product of num1 and num2, also represented as a string.

#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
 };

// Add a node at the head of the list
void insertAtHead(ListNode* &head, int32_t value)
{
    ListNode *newNode = new ListNode(value);
    if(head) {
        newNode->next = head;
        head = newNode;
    } else {
        head = newNode;
    }
}

// Add node at the tail of the list
void insertAtTail(ListNode* &head, int32_t value)
{
    ListNode *newNode = new ListNode(value);
    if(head) {
        ListNode *tmp = head;
        while(tmp->next) tmp = tmp->next;
        tmp->next = newNode;
    } else {
        head = newNode;
    }
}

// Display link list
void display(ListNode *head) {
    ListNode *tmp = head;
    while(tmp) {
        cout << tmp->val;
        tmp = tmp->next;
    }
    cout << endl;
}

// Add two digits and save the result in the list
void addDigits(ListNode* &result, int d1, int d2, int& carry)
{
    int tmp = d1 + d2  + carry;
    int sum = tmp % 10;
    carry = tmp / 10;
    insertAtTail(result, sum);
}

// Reverse a link list
ListNode *reverseList(ListNode *head) {
    ListNode *prev {nullptr};
    ListNode *curr {nullptr};
    ListNode *nxt {head};

    while(nxt) {
        prev = curr;
        curr = nxt;
        nxt = nxt->next;
        curr->next = prev;
    }
    return curr;
}

// Function to add two numbers represented by linked list.
ListNode* addTwoLists(ListNode* first, ListNode* second)
{
    ListNode *result = nullptr;
    first = reverseList(first);
    second = reverseList(second);
    int carry = 0;

    while(first != nullptr && second != nullptr) {
        addDigits(result, first->val, second->val, carry);
        first = first->next;
        second = second->next;
    }

    while(first != nullptr) {
        addDigits(result, first->val, 0, carry);
        first = first->next;
    }

    while(second != nullptr) {
        addDigits(result, 0, second->val, carry);
        second = second->next;
    }
    if(carry != 0) insertAtTail(result, carry);
    result = reverseList(result);
    return result;
}

string multiply(string num1, string num2) {

    if(num1 == "0" || num2 == "0") return "0";

    ListNode *n1 {nullptr};
    ListNode *n2 {nullptr};
    // store numbers in reverse form for multiplication
    for(auto &c : num1) insertAtHead(n1, c - '0');
    for(auto &c : num2) insertAtHead(n2, c - '0');

    // List to store final result
    ListNode *result {nullptr};
    ListNode *second = n2;
    int32_t carry {};
    int32_t step {};

    // Multiple first number with a single digit from 2nd number
    while(second) {
        ListNode *tmpRes {nullptr};
        ListNode *first = n1;
        while(first) {
            auto s = (first->val * second->val) + carry;
            insertAtHead(tmpRes, s);
            first = first->next;
        }
        for(size_t i = 0; i < step; ++i) {
            insertAtTail(tmpRes, 0);
        }
        second = second->next;
        ++step;

        // Add current intermediate result to final answer
        result = addTwoLists(result, tmpRes);
    }

    ListNode *tmp = result;
    string strRes;
    while(tmp) {
        strRes.push_back(tmp->val + '0');
        tmp = tmp->next;
    }
    return strRes;
}

int main()
{
    string num1 = "2";
    string num2 = "3";
    cout << multiply(num1, num2) << endl;

    string a = "123";
    string b = "456";
    cout << multiply(a, b) << endl;

    string c = "498828660196";
    string d = "840477629533";
    cout << multiply(c, d) << endl;

    string e = "9133";
    string f = "0";
    cout << multiply(e, f) << endl;
}