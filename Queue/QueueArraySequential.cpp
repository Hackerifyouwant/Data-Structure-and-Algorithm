#include<iostream>

#define ll long long
#define endl '\n'

using namespace std;

class QueueArraySequential{
private:
    int capacity, front, back;
    int *queue;
    void DoubleCapacity();
public:
    QueueArraySequential():capacity(5),front(-1),back(-1){
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

void QueueArraySequential::DoubleCapacity (){
    
    capacity *= 2;
    int *newQueue = new int[capacity];

    int j = -1;
    for(int i = front+1; i <= back; i++){
        j++;
        newQueue[j] = queue[i];
    }
    front = -1;
    back = j;
    delete [] queue;
    queue = newQueue;
}

void QueueArraySequential::Push(int x){
    if(IsFull()){
        DoubleCapacity();
    }
    queue[++back] = x;
}

void QueueArraySequential::Pop(){
    if(IsEmpty()){
        cout << "Queue is empty.\n";
        return;
    }
    front++;        
}

bool QueueArraySequential::IsFull(){
    return (back + 1 == capacity);
}

bool QueueArraySequential::IsEmpty(){
    return (front == back);
}

int QueueArraySequential::getFront(){
    if (IsEmpty()) {
        cout << "Queue is empty.\n";
        return -1;
    }

    return queue[front+1];
}

int QueueArraySequential::getBack(){
    if (IsEmpty()) {
        cout << "Queue is empty.\n";
        return -1;
    }

    return queue[back];
}

int QueueArraySequential::getSize(){

    return (back - front);
}
int QueueArraySequential::getCapacity(){

    return capacity;
}

void printSequentialQueue (QueueArraySequential queue){
    cout << "front: " << queue.getFront() << "    back: " << queue.getBack() << "\n"
    << "capacity: " << queue.getCapacity() << "  number of elements: " << queue.getSize() << "\n\n";
}

int main(){
    QueueArraySequential q;
    if (q.IsEmpty()) {
        cout << "Queue is empty.\n\n";
    }
    q.Push(24);
    cout << "After push 24: \n";
    printSequentialQueue(q);
    q.Push(8);
    q.Push(23);
    cout << "After push 8, 23: \n";
    printSequentialQueue(q);
    q.Pop();
    cout << "After pop 24: \n";
    printSequentialQueue(q);
    q.Push(13);
    cout << "After push 13: \n";
    printSequentialQueue(q);
    q.Pop();
    cout << "After pop 8: \n";
    printSequentialQueue(q);
    q.Push(35);
    cout << "After push 35: \n";
    printSequentialQueue(q);
    q.Push(9);
    cout << "After push 9: \n";
    printSequentialQueue(q);
    return 0;
}