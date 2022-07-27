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

int getMiddle(Node *head)
{
    Node *slow = head;
    Node *fast = head;

    if(head) {
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
    }
    std::cout << "fast: " << fast << std::endl;
    return slow->data;
}

void createCycle(Node* &head, int pos) {
    Node *tmp = head;
    Node *loopStart = nullptr;
    int count = 1;

    while(tmp->next != NULL) {
        if(pos == count) loopStart = tmp;
        tmp = tmp->next;
        ++count;
    }
    tmp->next = loopStart;
}

bool detectCycle(Node* &head) {
    Node* slow = head;
    Node* fast = head;

    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast) {
            std::cout << "loop detected at node: " << slow->data << std::endl;
            return true;
        }
    }
    return false;
}

void removeCycle(Node* &head)
{
    Node* slow = head;
    Node *fast = head;

    do
    {
        slow = slow->next;
        fast = fast->next->next;
    } while(slow != fast);

    fast = head;
    while(slow->next != fast->next) {
        slow = slow->next;
        fast = fast->next;
    }
    slow->next = nullptr;
}

void removeLoop(Node* head)
{
    Node* slow = head;
    Node* fast = head;

    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast) {
            slow = head;
            while(slow->next != fast->next) {
                slow = slow->next;
                fast = fast->next;
                std::cout << "moving to next pointer\n";
            }
            std::cout << slow->data << " " << fast->data << "\n";
            std::cout << "setting next of " << fast->data << " to nullptr\n";
            fast->next = nullptr;
        }
    }
}

// Recursive
Node* reverseList(Node *head, Node *prev = nullptr)
{
    if(head == nullptr) return prev;
    auto next = head->next;
    head->next = prev;
    return reverseList(next, head);
}

void display(Node* &head) {

    if(detectCycle(head)) {
        std::cout << "Linked list contains loop, it can't be displayed\n";
        return;
    }

    Node *t = head;
    while(t != nullptr) {
        std::cout << t->data << " -> ";
        t = t->next;
    }
    std::cout << std::endl;
}

int main()
{
    // Remove loop in a list
    Node* head = nullptr;
    insertAtTail(head, 7);
    insertAtTail(head, 58);
    insertAtTail(head, 36);
    insertAtTail(head, 34);
    insertAtTail(head, 16);

    createCycle(head, 1);
    std::cout << detectCycle(head) << std::endl;
    removeLoop(head);
    display(head);

    // Node *head = nullptr;
    // for(int i = 1; i < 6; ++i) insertAtTail(head, i);
    // // std::cout << "head: " << head << std::endl;
    // display(head);
    // head = reverseList(head);
    // display(head);



    // std::cout << "head: " << head << std::endl;
    // // std::cout << "Middle: " << getMiddle(head) << std::endl;
    // createCycle(head, 3);
    // std::cout << detectCycle(head) << std::endl;
    // std::cout << "head: " << head << std::endl;
    // removeLoop(head);
    // std::cout << detectCycle(head) << std::endl;
    // display(head);
}