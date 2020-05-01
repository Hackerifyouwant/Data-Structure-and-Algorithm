#include<iostream>

#define ll long long 
#define endl '\n'

using namespace std;

class LinkedList;

class ListNode{
private:
    int data;
    ListNode *next;
public:
    ListNode():data(0),next(0){};
    ListNode(int a):data(a),next(0){};

    friend class LinkedList;
};

class LinkedList{
private:
    ListNode *first;
public:
    LinkedList():first(0){};
    void PrintList();
    void Push_front(int x);
    void Push_back(int x);
    void Delete(int x);
    void Clear();
    void Reverse();
};

void LinkedList::PrintList(){
    if(first == 0){
        cout << "List is empty.\n";
        return;
    }

    ListNode *current = first;
    while(current != 0){
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void LinkedList::Push_front(int x){
    
    ListNode *newNode = new ListNode(x);
    newNode->next = first;
    first = newNode;

}

void LinkedList::Push_back(int x){
    ListNode *newNode = new ListNode(x);
    if(first == 0){
        first = newNode;
        return ;
    }
    
    ListNode *current = first;
    while(current->next != 0){
        current = current->next;
    }
    current->next = newNode;

}

void LinkedList::Delete(int x){
    ListNode *current = first, *previous = 0;
    while(current != 0 && current->data != x){
        previous = current;
        current = current->next;
    }

    if(current == 0){
        cout << "There is no " << x << " in list.\n";
    }else if(current == first){
        first = current->next;
        delete current;
        current = 0;
    }else{
        previous->next = current->next;
        delete current;
        current = 0;
    }
}

void LinkedList::Clear(){
    while(first != 0){
        ListNode *current = first;
        first = first->next;
        delete current;
        current = 0;
    }
}

void LinkedList::Reverse(){
    if(first == 0||first->next == 0){
        return;
    }
    ListNode *previous = 0,
             *current = first,
             *preceding = first->next;
    while(preceding != 0){
        current->next = previous;
        previous = current;
        current = preceding;
        preceding = preceding->next;
    }         
    current->next = previous;
    first = current;
}
int main(){
    LinkedList list;     // 建立LinkedList的object
    list.PrintList();    // 目前list是空的
    list.Delete(4);      // list是空的, 沒有4
    list.Push_back(5);   // list: 5
    list.Push_back(3);   // list: 5 3
    list.Push_front(9);  // list: 9 5 3
    list.PrintList();    // 印出:  9 5 3
    list.Push_back(4);   // list: 9 5 3 4
    list.Delete(9);      // list: 5 3 4
    list.PrintList();    // 印出:  5 3 4
    list.Push_front(8);  // list: 8 5 3 4
    list.PrintList();    // 印出:  8 5 3 4
    list.Reverse();      // list: 4 3 5 8
    list.PrintList();    // 印出:  4 3 5 8
    list.Clear();        // 清空list
    list.PrintList();    // 印出: List is empty.

    return 0;
}