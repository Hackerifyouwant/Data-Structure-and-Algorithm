#include <iostream>

#define ll long 
#define endl '\n'

using namespace std;

class QueueArrayCircular{
private:
    int capacity, front, back;
    int *queue;
    void DoubleCapacity();
public:
    QueueArrayCircular():capacity(5),front(0),back(0){     
        queue = new int[capacity];
    }
    void Push(int x);
    void Pop();
    bool IsEmpty();
    bool IsFull();
    int getFront();
    int getBack();
    int getSize();
    int getCapacity();   
};

void QueueArrayCircular::DoubleCapacity(){

    int *newQueue = new int[capacity*2];

    int j = front, size = getSize();
    for (int i = 1; i <= size; i++) {
        newQueue[i] = queue[++j % capacity];    
    }

    back = getSize();  
    front = 0;          
    capacity *= 2;

    delete [] queue;
    queue = newQueue;
}
void QueueArrayCircular::Push(int x){

    if (IsFull()) {
        DoubleCapacity();
    }

    back = (back + 1)%capacity;
    queue[back] = x;
}
void QueueArrayCircular::Pop(){

    if (IsEmpty()) {
        cout << "Queue is empty.\n";
        return;
    }

    front = (front + 1)%capacity;
}
bool QueueArrayCircular::IsEmpty(){

    return (front == back);
}
bool QueueArrayCircular::IsFull(){

    return ((back + 1)%capacity == front);
}
int QueueArrayCircular::getFront(){

    if (IsEmpty()) {
        cout << "Queue is empty.\n";
        return -1;
    }
    return queue[(front + 1)%capacity];
}
int QueueArrayCircular::getBack(){

    if (IsEmpty()) {
        cout << "Queue is empty.\n";
        return -1;
    }

    return queue[back];
}
int QueueArrayCircular::getSize(){

    int size;
    if (front < back) {
        size = back - front;
    }
    else {
        size = capacity - (front - back);
    }

    return size;
}
int QueueArrayCircular::getCapacity(){

    return capacity;
}

void printCircularQueue (QueueArrayCircular queue){
    cout << "front: " << queue.getFront() << "    back: " << queue.getBack() << "\n"
    << "capacity: " << queue.getCapacity() << "  number of elements: " << queue.getSize() << "\n\n";
}

int main(){

    QueueArrayCircular q;
    if (q.IsEmpty()) {
        cout << "Queue is empty.\n\n";
    }
    q.Push(24);
    cout << "After push 24:\n";
    printCircularQueue(q);
    q.Push(8);
    q.Push(23);
    cout << "After push 8, 23:\n";
    printCircularQueue(q);
    q.Pop();
    cout << "After pop 24:\n";
    printCircularQueue(q);
    q.Push(13);
    cout << "After push 13:\n";
    printCircularQueue(q);
    q.Pop();
    cout << "After pop 8:\n";
    printCircularQueue(q);
    q.Push(35);
    cout << "After push 35:\n";
    printCircularQueue(q);
    q.Push(9);
    cout << "After push 9:\n";
    printCircularQueue(q);
    q.Push(64);
    cout << "After push 64:\n";
    printCircularQueue(q);
    return 0;
}