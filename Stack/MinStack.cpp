#include<iostream>
#include<stack>

#define ll long long
#define endl '\n'

using namespace std;

class MinStack{
private:
    stack<int>data;
    stack<int>minstack;
public:
    MinStack(){};
    void Push(int x);
    void Pop();
    bool IsEmpty();
    int Top();
    int getSize();
    int getMin();
};

void MinStack::Push(int x){
    data.push(x);
    if(minstack.empty() || x < minstack.top()){
        minstack.push(x);
    }else{
        minstack.push(minstack.top());
    }
}

void MinStack::Pop(){
    if(data.empty()){
        cout << "Stack is empty.\n";
        return;
    }
    data.pop();
    minstack.pop();    
}

int MinStack::getMin(){
    if(data.empty()){
        cout << "Stack is empty.\n";
        return -1;
    }
    return minstack.top();
}

bool MinStack::IsEmpty(){
    return data.empty();
}

int MinStack::Top(){
    if(data.empty()){
        cout << "Stack is empty.\n";   
        return -1;   
    }
    return data.top();
}

int MinStack::getSize(){
    if(data.empty()){
        cout << "Stack is empty.\n";
        return -1;
    }
    return data.size();
}

int main(){
    MinStack s;
    s.Pop();
    s.Push(6);
    cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;
    ·
    s.Push(13);
    cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

    s.Push(4);
    cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

    s.Push(9);
    cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

    s.Push(1);
    cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

    s.Pop();
    cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

    s.Pop();
    cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

    s.Pop();
    cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

    s.Pop();
    cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;

    s.Pop();
    cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << endl;
    
    return 0;
}