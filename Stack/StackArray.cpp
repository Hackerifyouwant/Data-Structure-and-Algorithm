#include<iostream>

#define ll long long
#define endl '\n'

using namespace std;

class StackArray{
private:
    int top;
    int capacity;
    int *stack;
    void DoubleCapacity();
public:
    StackArray():top(-1),capacity(1){
        stack = new int[capacity];
    }
    void Push(int x);
    void Pop();
    bool IsEmpty();
    int Top();
    int getSize();
};
void StackArray::DoubleCapacity (){
    capacity *= 2;
    int *newStack = new int[capacity];

    for(int i = 0; i < capacity/2; i++){
        newStack[i] = stack[i];
    }

    delete [] stack;
    stack = newStack;
}

void StackArray::Push(int x){
    if(top == capacity - 1){
        DoubleCapacity();
    }
    stack[++top] = x;
}

void StackArray::Pop(){
    if(IsEmpty()){
        cout << "Stack is empty.\n";
        return;
    }
    top--;
}

bool StackArray::IsEmpty(){
    return (top == -1);
}

int StackArray::Top(){
    if(IsEmpty()){
        cout << "Stack is empty.\n";
        return -1;
    }
    return stack[top];
}

int StackArray::getSize(){
    return top+1;
}

int main(){
    StackArray s;
    s.Pop();
    s.Push(14);
    s.Push(9);
    cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;
    s.Push(7);
    cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;
    s.Pop();
    s.Pop();
    cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl; 
    s.Pop();
    cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;

    return 0;
}