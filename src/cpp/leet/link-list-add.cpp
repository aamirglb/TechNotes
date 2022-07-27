#include <iostream>
#include <memory>
#include <deque>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int x){
        data = x;
        next = nullptr;
    }
};

void insertAtTail(Node* &head, int data) {
    Node *tmp = new Node(data);
    if(head == nullptr) {
        head = tmp;
    } else {
        Node *t = head;
        while(t->next != nullptr) t = t->next;
        t->next = tmp;
    }
}

Node* reverseList(Node *head, Node *prev = nullptr)
{
    if(head == nullptr) return prev;
    auto next = head->next;
    head->next = prev;
    return reverseList(next, head);
}

void display(Node* &head) {
    Node *curr = head;
    while(curr != nullptr) {
        std::cout << curr->data << " -> ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

void addDigits(Node* &result, int d1, int d2, int& carry)
{
    int tmp = d1 + d2  + carry;
    int sum = tmp % 10;
    carry = tmp / 10;
    insertAtTail(result, sum);
}

Node* getMiddleNode(Node *head) {
    Node* slow = head;
    Node* fast = head->next;

    while(fast != nullptr && fast->next != nullptr) {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

Node* addTwoLists(struct Node* first, struct Node* second)
{
    Node *result = nullptr;
    first = reverseList(first);
    second = reverseList(second);
    int carry = 0;

    while(first != nullptr && second != nullptr) {
        addDigits(result, first->data, second->data, carry);
        first = first->next;
        second = second->next;
    }

    while(first != nullptr) {
        addDigits(result, first->data, 0, carry);
        first = first->next;
    }

    while(second != nullptr) {
        addDigits(result, 0, second->data, carry);
        second = second->next;
    }
    if(carry != 0) insertAtTail(result, carry);
    result = reverseList(result);
    display(result);
    return result;
}

bool isPalindrome(Node *head)
{
    Node* mid = getMiddleNode(head);
    mid->next = reverseList(mid->next);
    Node* left = head;
    Node* right = mid->next;
    while(right != nullptr) {
        if(left->data != right->data) return false;
        left = left->next;
        right = right->next;
    }
    return true;
}

int main()
{
    // Node *head1 = nullptr;
    // // insertAtTail(head1, 1);
    // // insertAtTail(head1, 5);
    // insertAtTail(head1, 3);

    // Node *head2 = nullptr;
    // // insertAtTail(head2, 2);
    // insertAtTail(head2, 6);
    // insertAtTail(head2, 7);

    // addTwoLists(head1, head2);

    // Node* head = nullptr;
    // insertAtTail(head, 1);
    // insertAtTail(head, 2);
    // insertAtTail(head, 3);
    // insertAtTail(head, 4);
    // insertAtTail(head, 2);
    // insertAtTail(head, 1);

    // std::cout << "palindrom: " << isPalindrome(head) << std::endl;
}

