#include<iostream>

#define ll long long
#define endl '\n'

using namespace std;

class StackList;

class StackNode{
private:
    int data;
    StackNode *next;
public:
    StackNode():data(0){
        next = 0;
    }    
    StackNode(int x):data(x){
        next = 0;
    }
    StackNode(int x, StackNode *newNode):data(x),next(newNode){};
    friend class StackList;
};

class StackList{
private:
    StackNode *top;
    int size;
public:
    StackList():size(0),top(0){};
    void Push(int x);
    void Pop();
    bool IsEmpty();
    int Top();
    int getSize();
};

void StackList::Push(int x){
    if(IsEmpty()){
        top = new StackNode(x);
        size++;
        return;
    }

    StackNode *newNode = new StackNode(x);
    newNode->next = top;
    top = newNode;
    size++;
}

void StackList::Pop(){
    if(IsEmpty()){
        cout << "Stack is empty.\n";
        return;
    }

    StackNode *deleteNode = top;
    top = top->next;
    delete deleteNode;
    deleteNode = 0;
    size--; 
}

bool StackList::IsEmpty(){
    return (size == 0);
}

int StackList::Top(){
    if(IsEmpty()){
        cout << "Stack is empty.\n";
        return -1; 
    }
    return top->data;
}

int StackList::getSize(){
    return size;
}

int main(){
    StackList s;
    s.Pop();
    s.Push(32);
    s.Push(4);
    cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;        
    s.Push(15);
    cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;         
    s.Pop();
    s.Pop();
    cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;          
    s.Pop();
    cout << "\ntop: " << s.Top() << "\nsize: " << s.getSize() << endl;
    return 0;
}