#include<iostream>
#include<vector>
#include<math.h>

#define ll long long
#define endl '\n'

using namespace std;

struct HeapNode{
    int element, key;
    HeapNode():element(0), key(0){};
    HeapNode(int node, int key):element(node),key(key){};
};

class BinaryHeap{
private:
    vector<HeapNode> heap;
    void swap(HeapNode &p1, HeapNode&p2);
    int Findposition(int node);
    int GetParentNode(int node){return floor(node/2);};
public:
    BinaryHeap(){
        heap.resize(1);
    }
    BinaryHeap(int n){
        heap.resize(n + 1);
    }
    bool IsHeapEmpty(){return (heap.size()<1);};

    void MinHeapify(int node, int length);
    void BuildMinHeap(vector<int> array);
    void DecreaseKey(int node, int newKey);
    void MinHeapInsert(int node, int key);
    int Minimum();
    int ExtracMin();
};

void BinaryHeap::MinHeapify(int node, int length){
    int left = 2*node;
    int right = 2*node + 1;
    int smallest;

    if(left <= length && heap[left].key < heap[node].key)
        smallest = left;
    else
        smallest = node;
    
    if(right <= length && heap[right].key < heap[node].key)
        smallest = right;
    if(smallest != node){
        swap(heap[smallest], heap[node]);
        MinHeapify(smallest, length);
    }
}

void BinaryHeap::BuildMinHeap(vector<int> array){

    for(int i = 0; i < array.size(); i++){
        heap[i + 1].element = i;
        heap[i + 1].key = array[i];
    }
    for(int i = (int)heap.size()/2; i >= 1; i--){
        MinHeapify(i, (int)heap.size() - 1);
    }
}

void BinaryHeap::swap(HeapNode &p1, HeapNode &p2){
    HeapNode temp = p1;
    p1 = p2;
    p2 = temp;
}

int BinaryHeap::Findposition(int node){
    int idx = 0;
    for(int i = 0; i < heap.size(); i++){
        if(heap[i].element == node){
            idx = i;
        }
    }
    return idx;
}

int BinaryHeap::Minimum(){
    return heap[1].element;
}

int BinaryHeap::ExtracMin(){
    if(IsHeapEmpty()){
        cout << "error: heap is empty\n";
        exit(-1);
    }
    int min = heap[1].element;

    heap[1] = heap[heap.size() - 1];
    heap.erase(heap.begin() + heap.size() - 1);
    MinHeapify(1,(int)heap.size());

    return min;
}

void BinaryHeap::DecreaseKey(int node, int newKey){
    int index_node = Findposition(node);

    if(newKey > heap[index_node].key){
        cout << "new key is larger than current key\n";
        return;
    }

    heap[index_node].key = newKey;
    while(index_node > 1 && heap[GetParentNode(index_node)].key > heap[index_node].key){
        swap(heap[index_node], heap[GetParentNode(index_node)]);
        index_node = GetParentNode(index_node);
    }
}
void BinaryHeap::MinHeapInsert(int node, int key){
    heap.push_back(HeapNode(node, key));
    DecreaseKey(node, key);
}


int main(){

    return 0;
}