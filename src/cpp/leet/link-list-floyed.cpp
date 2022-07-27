#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int x) {
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

void display(Node* &head) {
    Node *t = head;
    while(t != nullptr) {
        std::cout << t->data << " -> ";
        t = t->next;
    }
    std::cout << std::endl;
}

Node* floydCycleDetection(Node* head)
{
    if(head == nullptr) return nullptr;

    Node* slow = head;
    Node* fast = head;

    while(fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if(slow == fast) {
            // std::cout << "cycle detected. Node in the loop: " << slow->data << std::endl;
            return slow;
        }
    }
    return nullptr;
}

Node* getLoopStart(Node* head)
{
    if(head == nullptr) return nullptr;

    Node* intersection = floydCycleDetection(head);
    std::cout << "Intersection point: " << intersection->data << endl;
    Node* slow = head;

    while(slow != intersection) {
        std::cout << slow->data << " " << intersection->data << "\n";
        slow = slow->next;
        intersection = intersection->next;
        // cout << "looping...\n";
    }
    return slow;
}

void removeLoop(Node* head)
{
    if(head == nullptr) return;

    Node* loopStart = getLoopStart(head);
    Node* tmp = loopStart;
    while(tmp->next != loopStart) {
        tmp = tmp->next;
    }
    tmp->next = nullptr;
}

Node* pairWiseSwap(struct Node* head)
{
    Node* curr = head;

    while(curr->next != nullptr) {
        Node *tmp = curr->next;
        Node* next = curr->next;
        curr->next = tmp->next;
        next->next = curr;
        curr = tmp->next->next;
        display(head);
    }
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
    display(head);

    Node* newHead = new Node(0);
    newHead->next = head;
    Node* curr = newHead;

    while(curr != nullptr) {
        Node* first = curr->next;
        Node* second = nullptr;

        if(first != nullptr) second = first->next;

        if(second != nullptr) {
            Node *secondNext = second->next;
            second->next = first;
            curr->next = second;
            first->next = secondNext;
            curr = first;
        } else {
            break;
        }
    }

    // createCycle(head, 1);
    // if(floydCycleDetection(head) != nullptr) {
    //     std::cout << "cycle present.\n";
    // }

    // Node* loop = getLoopStart(head);

    // std::cout << "Loop start at " << loop->data << std::endl;
    // removeLoop(head);
    // display(head);

    // pairWiseSwap(head);
    display(newHead->next);

}