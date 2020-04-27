#include<iostream>

#define ll long long
#define endl '\n'

using namespace std;

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <iomanip>      // for setw()

class Graph{
private:
    int num_vertex;
    vector< std::list<int> > AdjList;
    int *color,             // 0:white, 1:gray, 2:black
        *distance,
        *predecessor,
        *discover,
        *finish;

public:
    Graph():num_vertex(0){};
    Graph(int N):num_vertex(N){
        // initialize Adj List
        AdjList.resize(num_vertex);
    };

    int GetColor(int i){return color[i];};
    int GetFinish(int i){return finish[i];};
    int GetPredecessor(int i){return predecessor[i];};

    void AddEdgeList(int from, int to);

    void BFS(int Start);
    void DFS(int Start);
    void DFSVisit(int vertex, int &time);
    void VariableInitializeDFS();

    void CCDFS(int vertex);     // 吃一個int, 表示起點vertex, 若沒給就從0開始
    void CCBFS(int vertex = 0);
    void SetCollapsing(int vertex);
    void PrintDataArray(int *array);
    void PrintFinish();
    void PrintPredecessor();

    Graph GraphTranspose();
    void PrintSCCs(int Start = 0);

    friend void QuickSort(int *vec, int front, int end, int *vec2);
    friend int Partition(int *vec, int front, int end, int *vec2);
    friend void swap(int *x, int *y);

    void TopologicalSort(int Start = 0);
};

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
}

void Graph::DFS(int Start){
    color = new int[num_vertex];
    discover = new int[num_vertex];
    finish = new int[num_vertex];
    predecessor = new int[num_vertex];

    int time = 0;
    for(int i = 0; i < num_vertex; i++){
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }
    int i = Start;

    for(int j = 0; j < num_vertex; j++){
        if(color[i] == 0){
            DFSVisit(i , time);
        }
        i = j;
    }
}

void Graph::DFSVisit(int vertex, int &time){
    color[vertex] = 1;
    discover[vertex] = ++time;

    for(list<int>::iterator itr = AdjList[vertex].begin();
    itr != AdjList[vertex].end(); itr++){
        if(color[*itr] == 0){
            predecessor[*itr] = vertex;
            DFSVisit(*itr , time);
        }
        color[vertex] = 2;
        finish[vertex] = ++time;
    }
}
void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int Partition(int *vec, int front, int end, int *vec2){
    int pivot = vec[end];
    int i = front - 1;

    for(int j = front; j < end; j++){
        if(vec[j] > pivot){
            i++;
            swap(&vec[i], &vec[j]);
            swap(&vec2[i], &vec2[j]);
        }
    }
    swap(&vec[i + 1], &vec[end]);
    swap(&vec2[i + 1], &vec2[end]);

    return i + 1;  
}

void QuickSort(int *vec, int front, int end, int *vec2){
    if (front < end) {
        int pivot = Partition(vec, front, end, vec2);
        QuickSort(vec, front, pivot - 1, vec2);
        QuickSort(vec, pivot + 1, end, vec2);
    }
}

void Graph::TopologicalSort(int Start){
    DFS(Start);

    int finishLargetoSmall[num_vertex];
    for (int i = 0; i < num_vertex; i++) {
        finishLargetoSmall[i] = i;
    }

    QuickSort(finish, 0, num_vertex-1, finishLargetoSmall);

    cout << "Topological Sort:\n";
    for (int i = 0; i < num_vertex; i++)
        cout << setw(3) << finishLargetoSmall[i];
    cout << endl;
}

int main(){
    Graph g5(15);            // 建立如圖二(a)的DAG
    g5.AddEdgeList(0, 2);
    g5.AddEdgeList(1, 2);
    g5.AddEdgeList(2, 6);g5.AddEdgeList(2, 7);
    g5.AddEdgeList(3, 4);
    g5.AddEdgeList(4, 5);
    g5.AddEdgeList(5, 6);g5.AddEdgeList(5, 14);
    g5.AddEdgeList(6, 8);g5.AddEdgeList(6, 9);g5.AddEdgeList(6, 11);g5.AddEdgeList(6, 12);
    g5.AddEdgeList(7, 8);
    g5.AddEdgeList(9, 10);
    g5.AddEdgeList(12, 13);

    g5.TopologicalSort();
    g5.TopologicalSort(4);

    return 0;
}