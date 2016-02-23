#include "HeapPriorityQueue.h"

HeapPriorityQueue::HeapPriorityQueue() {
    capacity = 10;
    thisSize = 0;
    array = new PQEntry[capacity];
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete array;
}

void HeapPriorityQueue::changePriority(string value, int newPriority) {
    int i = 1;
    PQEntry current = array[i];
    while (current.value != value){
        current = array[++i];
        if (i >= capacity) throw "Error: element not found";
    }
    if (current.priority < newPriority) throw "Error: new priority is too high";
    array[i].priority = newPriority;
    while (true) {
        if (array[i].priority < array[i / 2].priority ||
                (array[i].priority == array[i / 2].priority &&
                 array[i].value < array[i / 2].value)) {
            swapElements(array[i], array[i / 2]);
            i /= 2;
        } else break;
    }
}

void HeapPriorityQueue::clear() {
    delete array;
    capacity = 10;
    thisSize = 0;
    array = new PQEntry[capacity];
}

string HeapPriorityQueue::dequeue() {
    string returnString = array[1].value;
    array[1] = array[thisSize];
    bubbleDown();
    thisSize--;
    return returnString;   // remove this
}

void HeapPriorityQueue::enqueue(string value, int priority) {
    array[++thisSize] = PQEntry(value, priority);
    bubbleUp();
}

bool HeapPriorityQueue::isEmpty() const {
    return thisSize == 0;
}

string HeapPriorityQueue::peek() const {
    return array[1].value;
}

int HeapPriorityQueue::peekPriority() const {
    return array[1].priority;
}

int HeapPriorityQueue::size() const {
    return thisSize;
}

ostream& operator<<(ostream& out, const HeapPriorityQueue& queue) {
    out << "{";
    for (int i = 1; i < queue.size() + 1; i++) {
        out << queue.array[i];
        if (i != queue.size()) out << ", ";
    }
    out << "}";
    return out;
}

void HeapPriorityQueue::checkResize() {
    if (thisSize == capacity - 1) {
        PQEntry* tempArray = new PQEntry[capacity * 2];
        for (int i = 1; i < thisSize; i++) {
            tempArray[i] = array[i];
        }
        delete[] array;
        array = tempArray;
        capacity *= 2;
    }
}

void HeapPriorityQueue::bubbleUp(){
    int currentIndex = thisSize;
    while (true) {
        if (currentIndex / 2 <= 0) break;
        if (array[currentIndex].priority < array[currentIndex / 2].priority ||
                (array[currentIndex].priority == array[currentIndex / 2].priority &&
                 array[currentIndex].value < array[currentIndex / 2].value)) {
            swapElements(array[currentIndex], array[currentIndex / 2]);
            currentIndex /= 2;
        } else break;
    }
}

void HeapPriorityQueue::bubbleDown(){
    int currentIndex = 1;
    int tempIndex;
    while (true) {
        PQEntry child1, child2, smallerChild;
        if (currentIndex * 2 > thisSize) break;
        else if (currentIndex * 2 == thisSize) {
            smallerChild = array[currentIndex * 2];
            tempIndex = currentIndex * 2;
        } else {
            child1 = array[currentIndex * 2];
            child2 = array[currentIndex * 2 + 1];
            if (child1.priority < child2.priority ||
                    (child1.priority == child2.priority &&
                     child1.value < child2.value)) {
                smallerChild = child1;
                tempIndex = currentIndex * 2;
            } else {
                smallerChild = child2;
                tempIndex = currentIndex * 2 + 1;
            }
        }

        if (smallerChild.priority < array[currentIndex].priority ||
                (smallerChild.priority == array[currentIndex].priority &&
                smallerChild.value < array[currentIndex].value)){
            swapElements(array[tempIndex], array[currentIndex]);
            currentIndex = tempIndex;
        } else break;
    }
}

void HeapPriorityQueue::swapElements(PQEntry &element1, PQEntry &element2) {
    PQEntry temp = element1;
    element1 = element2;
    element2 = temp;
}
