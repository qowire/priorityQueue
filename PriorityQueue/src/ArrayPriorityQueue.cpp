#include "ArrayPriorityQueue.h"

//sets capacity to 10
ArrayPriorityQueue::ArrayPriorityQueue() {
    thisSize = 0;
    capacity = 10;
    array = new PQEntry[capacity];
}

ArrayPriorityQueue::~ArrayPriorityQueue() {
    delete[] array;
}

void ArrayPriorityQueue::checkResize() {
    if (thisSize == capacity) {
        PQEntry* tempArray = new PQEntry[capacity * 2];
        for (int i = 0; i < thisSize; i++) {
            tempArray[i] = array[i];
        }
        delete[] array;
        array = tempArray;
        capacity *= 2;
    }
}

void ArrayPriorityQueue::changePriority(string value, int newPriority) {
    int i = 0;
    PQEntry* changeNode = &array[i++];
    while (changeNode->value != value) {
        changeNode = &array[i++];
        if (i >= thisSize) throw "Error: Value not found. ";
    }
    if (changeNode->priority < newPriority) throw "Error: Priority passed in is larger than current priority. ";
    PQEntry* temp = changeNode;
    changeNode = new PQEntry(temp->value, newPriority);
    delete temp;
    array[i-1] = *changeNode;
}

void ArrayPriorityQueue::clear() {
    delete[] array;
    thisSize = 0;
    capacity = 10;
    array = new PQEntry[capacity];
}

string ArrayPriorityQueue::dequeue() {
    if (isEmpty()) throw "Error: Queue is empty. ";
    PQEntry returnEntry = array[0];
    int entryIndex = 0;
    for (int i = 0; i < thisSize; i++) {
        if (array[i].priority < returnEntry.priority) {
            returnEntry = array[i];
            entryIndex = i;
        }
    }
    thisSize--;
    for (int i = entryIndex; i < thisSize; i++) {
        array[i] = array[i + 1];
    }
    return returnEntry.value;   // remove this
}

void ArrayPriorityQueue::enqueue(string value, int priority) {
    checkResize();
    array[thisSize++] = PQEntry (value, priority);
}

bool ArrayPriorityQueue::isEmpty() const {
    return thisSize == 0;
}

string ArrayPriorityQueue::peek() const {
    return getMostUrgentElement().value;
}

int ArrayPriorityQueue::peekPriority() const {
    return getMostUrgentElement().priority;
}

int ArrayPriorityQueue::size() const {
    return thisSize;
}

ostream& operator<<(ostream& out, const ArrayPriorityQueue& queue) {
    out << "{";
    for (int i = 0; i < queue.size(); i++) {
        out << queue.array[i];
        if (i != queue.size() - 1) out << ", ";
    }
    out << "}";
    return out;
}

PQEntry ArrayPriorityQueue::getMostUrgentElement() const {
    PQEntry returnElement = array[0];
    for (int i = 0; i < thisSize; i++) {
        if (array[i].priority < returnElement.priority) {
            returnElement = array[i];
        }
    }
    return returnElement;
}
