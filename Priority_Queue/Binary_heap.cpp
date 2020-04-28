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
};

int main(){

    return 0;
}