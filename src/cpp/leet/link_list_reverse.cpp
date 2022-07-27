#include <iostream>
#include <initializer_list>

struct Node {
    int32_t   data;
    Node*     next;

    Node(int32_t d = 0)
        : data { d }
        , next {nullptr}
    {}
};

void display(Node *head)
{
    Node *tmp = head;
    while(tmp->next) {
        std::cout << tmp->data << " -> ";
        tmp = tmp->next;
    }
    std::cout << tmp->data << std::endl;
}

void insertAtTail(Node* &head, int32_t x)
{
    Node *tmp = head;
    while(tmp->next != nullptr) tmp = tmp->next;
    Node* newNode = new Node(x);
    tmp->next = newNode;
}

void insertAtTail(Node* head, std::initializer_list<int32_t> values)
{
    Node *tail = head;
    while(tail->next != nullptr) tail = tail->next;

    for(auto & ele : values) {
        Node *tmp = new Node(ele);
        tail->next = tmp;
        tail = tmp;
    }
}

void insertAtHead(Node* &head, int32_t x)
{
    Node* tmp = new Node(x);
    tmp->next = head;
    head = tmp;
}


// reverse using sliding pointers
Node* reverseList(Node *head)
{
    Node* prev {nullptr};
    Node* curr {nullptr};
    Node* next {head};

    while(next) {
        prev = curr;
        curr = next;
        next = next->next;
        curr->next = prev;
    }
    return curr;
}

// Node* reverseList(Node *head, Node *prev = nullptr)
// {
//     if(head == nullptr) return prev;
//     auto next = head->next;
//     head->next = prev;
//     return reverseList(next, head);
// }

// Recursive reverse
void recursiveReverse(Node *curr, Node *prev, Node* &head)
{
    if(curr != nullptr) {
        recursiveReverse(curr->next, curr, head);
        curr->next = prev;
    } else {
        head = prev;
    }
}

Node* mergeLinkList(Node *first, Node *second)
{
    Node *last { nullptr };
    Node *third { nullptr };

    if(!first || !second) return nullptr;

    if(first->data < second->data) {
        last = first;
        third = first;
        first = first->next;
        last->next = nullptr;
    } else {
        last = second;
        third = second;
        second = second->next;
        last->next = nullptr;
    }

    while(first && second) {
        if(first->data < second->data) {
            last->next = first;
            last = first;
            first = first->next;
            last->next = nullptr;
        } else {
            last->next = second;
            last = second;
            second = second->next;
            last->next = nullptr;
        }
    }
    if(first) last->next = first;
    else last->next = second;
    return third;
}
int main()
{
    Node *head {nullptr};
    insertAtHead(head, 10);
    insertAtTail(head, {1, 3, 5, 7});
    // insertAtHead(head, 5);
    // insertAtHead(head, 3);
    // insertAtTail(head, 15);
    // insertAtTail(head, 20);
    // insertAtHead(head, 2);

    display(head);

    head = reverseList(head);
    display(head);

    insertAtTail(head, 1);
    display(head);

    recursiveReverse(head, nullptr, head);
    display(head);

    std::cout << "\n\n";

    Node *first = nullptr;
    insertAtHead(first, 1);
    insertAtTail(first, {3, 5, 7, 9, 11});

    Node *second = nullptr;
    insertAtHead(second, 2);
    insertAtTail(second, {4, 6, 8, 10});

    Node *third = mergeLinkList(first, second);
    display(third);

    third = reverseList(third);
    display(third);
}