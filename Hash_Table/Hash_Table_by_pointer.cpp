#include<iostream>
#include<vector>
#include<string>
#include<math.h>


#define endl '\n'
#define ll long long

using namespace std;

struct Node{
    int key;
    string value;
    Node *next;

    Node():key(0),value(""),next(0){};
    Node(int Key, string Value):key(Key),value(Value),next(0){};
    Node(Node const &data):key(data.key),value(data.value),next(data.next){};
};

class HashChainNode{
private: 
    int size;
    int count;
    Node **table;

    int HashFunction(int key);
    void TableDoubling();
    void TableShrinking();
    void Rehashing(int size_orig);
public:
    HashChainNode(){};
    HashChainNode(int m):size(m),count(0){
        table = new Node *[size];
        for(int i = 0; i < size; i++){
            table[i] = 0;
        }
    }
    ~HashChainNode();

    void Insert(Node data);
    void Delete(int key);
    string Search(int key);
    void DisplayTable();
};

void HashChainNode::Insert(Node data){
    count ++;
    if(count > size){
        TableDoubling();
    }

    int index = HashFunction(data.key);
    Node *newNode = new Node(data);

    if(table[index] == NULL){
        table[index] = newNode;
    }else{
        Node *next = table[index]->next;
        table[index]->next = newNode;
        newNode->next = next;
    }
}

void HashChainNode::Delete(int key){

    int index = HashFunction(key);
    Node *current = table[index];
    Node *previous = NULL;

    while(current != NULL && current->key != key){
        previous = current;
        current = current->next;
    }
    
    if (current == NULL) {                    // eg: list:5->2->9->NULL, want to delete 3
        cout << "data not found.\n\n";
        return;
    }else{
        if(previous == NULL){
            table[index] = current->next;
        }else{
            previous->next = current->next;
        }
        delete current;
        current = 0;
    }
    count --;
    if(count < size/4){
        TableShrinking();
    }
}
string HashChainNode::Search(int key){
    int index = HashFunction(key);
    Node *current = table[index];

    while(current != NULL){
        if(current->key == key){
            return current->value;
        }
        current = current->next;
    }
    return "...\nno such data";
}

int HashChainNode::HashFunction (int key){
    double A = 0.6180339887;
    int frac = key*A - floor(key*A);
    return floor(this->size*frac);
}
void HashChainNode::TableDoubling (){
    int size_orig = size;
    size *= 2;
    Rehashing(size_orig);
}

void HashChainNode::TableShrinking (){
    int size_orig = size;
    size /= 2;
    Rehashing(size_orig);
}

void HashChainNode::Rehashing (int size_orig){
    Node **newtable = new Node *[size];
    for(int i = 0; i < size; i++){
        newtable[i] = 0;
    }

    for(int i = 0; i < size_orig; i++){
        Node *curr_orig = table[i];
        Node *prev_orig = NULL;

        while(curr_orig != NULL){

            prev_orig = curr_orig->next;

            int index = HashFunction(curr_orig->key);

            if(newtable[index] == NULL){
                newtable[index] = curr_orig;
                newtable[index]->next = 0; 
            }else{
                Node *next = newtable[index]->next;
                newtable[index]->next = curr_orig;
                curr_orig->next = next;            
            }
            curr_orig = prev_orig;
        } 
    }
    delete [] table;
    this->table = newtable;
}

HashChainNode::~HashChainNode(){
    for(int i = 0; i < size; i++){
        Node *current = table[i];
        while(current != NULL){
            Node *previous = current;
            current = current->next;
            delete previous;
            previous = 0;
        }
    }
    delete [] table;
}

void HashChainNode::DisplayTable(){

    for (int i = 0; i < size; i++) {    // visit every node in table 
        cout << "#slot#" << i << ": ";
        Node *current = table[i];
        while (current != NULL) {
            cout << "(" << current->key << "," << current->value << ") ";
            current = current->next;
        }
        cout << endl;
    }
    cout << endl;
}


int main(){
    HashChainNode hash(2);

    hash.Insert(Node(12,"post rock"));
    hash.Insert(Node(592,"shoegaze"));
    cout << "After inserting key(12),key(592):\n";
    hash.DisplayTable();
    hash.Insert(Node(6594,"blues"));        // evoke TableDoubling()
    cout << "After inserting key(6594), evoke TableDoubling():\n";
    hash.DisplayTable();
    hash.Insert(Node(7,"folk"));
    cout << "After inserting key(7):\n";
    hash.DisplayTable();
    hash.Insert(Node(123596,"hiphop"));     // evoke TableDoubling()
    cout << "After inserting key(123596), evoke TableDoubling():\n";
    hash.DisplayTable();
    hash.Insert(Node(93,"soul"));
    hash.Insert(Node(2288,"indie"));
    hash.Insert(Node(793,"jazz"));
    cout << "After inserting key(93),key(2288),key(793):\n";
    hash.DisplayTable();
    hash.Insert(Node(8491,"electro"));      // evoke TableDoubling()
    cout << "After inserting key(8491), evoke TableDoubling():\n";
    hash.DisplayTable();
    hash.Insert(Node(323359,"pop"));
    cout << "After inserting key(323359):\n";
    hash.DisplayTable();

    cout << "Searching: genre(8491) is " << hash.Search(8491) << ".\n\n";
    cout << "Searching: genre(7) is " << hash.Search(7) << ".\n\n";

    hash.Delete(7);
    cout << "After deleting key(7):\n";
    cout << "Searching: genre(7) is " << hash.Search(7) << ".\n\n";

    hash.Delete(592);
    cout << "After deleting key(592):\n";
    hash.DisplayTable();

    cout << "Want to  delete key(592) again:\n";
    hash.Delete(592);

    hash.Delete(123596);
    hash.Delete(323359);
    hash.Delete(793);
    hash.Delete(93);
    cout << "After deleting key(123596),key(323359),key(793),key(93):\n";
    hash.DisplayTable();

    hash.Delete(6594);      // evoke TableShrinking()
    cout << "After deleting key(6594), evoke TableShrinking():\n";
    hash.DisplayTable();


    return 0;
}