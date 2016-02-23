#include "LinkedPriorityQueue.h"

LinkedPriorityQueue::LinkedPriorityQueue() {
    thisSize = 0;
    front = NULL;
}

LinkedPriorityQueue::~LinkedPriorityQueue() {
    clear();
}

void LinkedPriorityQueue::changePriority(string value, int newPriority) {
    if (!front) throw "Error: No elements in Queue. ";
    ListNode* current = front;
    ListNode* last = current;
    while (current->value != value) {
        if (!current->next) throw "Error: value not found. ";
        last = current;
        current = current->next;
    }
    if (current->priority < newPriority) throw "Error: new priority is less than existing priority. ";
    last->next = current->next;
    enqueue(current->value, newPriority);
    thisSize--;
    delete current;
    current->priority = newPriority;
}

void LinkedPriorityQueue::clear() {
    if (front) {
        clearHelper(front);
        thisSize = 0;
        front = NULL;
    }
}

void LinkedPriorityQueue::clearHelper(ListNode* node) {
    if (node->next) {
        clearHelper(node->next);
    }
    delete node;
}

string LinkedPriorityQueue::dequeue() {
    if (thisSize == 0) throw "Error: No elements left in collection. ";
    ListNode* returnNode = front;
    front = front->next;
    string returnString = returnNode->value;
    delete returnNode;
    thisSize--;
    return returnString;
}

void LinkedPriorityQueue::enqueue(string value, int priority) {
    ListNode* current = front;
    if (current) { // if there are no elements, set the front to be the correct element
        if (current->priority > priority) {
            front = new ListNode(value, priority, current);
        } else {
            while (current->next && current->next->priority < priority) { //this loop gets the index before the point where the new node should be inserted
                current = current->next;
            }
            if (current->next) {
                current->next = new ListNode(value, priority, current->next);
            } else {
                current->next = new ListNode(value, priority, NULL);
            }
        }
    } else {
        front = new ListNode(value, priority, NULL);
    }
    thisSize++;
}

bool LinkedPriorityQueue::isEmpty() const {
    return thisSize == 0;
}

string LinkedPriorityQueue::peek() const {
    if (thisSize == 0) throw "Error: no elements found";
    return front->value;
}

int LinkedPriorityQueue::peekPriority() const {
    if (thisSize == 0) throw "Error: no elements found";
    return front->priority;
}

int LinkedPriorityQueue::size() const {
    return thisSize;
}

ostream& operator<<(ostream& out, const LinkedPriorityQueue& queue) {
    out << "{";
    if (queue.front) {
        ListNode* current = queue.front;
        while (true) {
            out << *current;
            if (current->next) {
                out << ", ";
                current = current->next;
            } else break;
        }
    }
    out << "}";
    return out;
}
