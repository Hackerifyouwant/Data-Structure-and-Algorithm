#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <iomanip>
#define ll long long
#define endl '\n'

using namespace std;

class Graph{
private:
    int num_vertex;
    vector< std::list<int> > AdjList;
    int *color,             // 0:white, 1:gray, 2:black
        *predecessor,
        *distance,          // for BFS()
        *discover,          // for DFS()
        *finish;
public:
    Graph():num_vertex(0){};
    Graph(int N):num_vertex(N){
        // initialize Adj List
        AdjList.resize(num_vertex);
    };

    int GetColor(int i){return color[i];};
    int GetFinsish(int i){return finish[i];};
    int GetPredecessor(int i){return predecessor[i];};

    void AddEdgeList(int from, int to);
    
    void DFS(int Start);
    void BFS(int Start);
    void DFSVisit(int vertex, int &time);
    void VariableInitializeDFS();

    void CCDFS(int vertex);                // 利用DFS 
    void CCBFS(int vertex = 0);            // 利用BFS, 兩者邏輯完全相同
    void SetCollapsing(int vertex);
    void PrintDataArray(int *array);
    void PrintFinish();
    void PrintPredecessor();               // 印出predecessor, 供驗証用, 非必要

    Graph GraphTranspose();
    void PrintSCCs(int Start = 0);

    friend void QuickSort(int *vec, int front, int end, int *vec2);
    friend int Partition(int *vec, int front, int end, int *vec2);
    friend void swap(int *x, int *y);
};

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

void Graph::PrintSCCs(int Start){
    DFS(Start);

    cout << "First DFS() on G, finish time:" << endl;
    PrintFinish();

    Graph gT(num_vertex);
    gT  = GraphTranspose();

    int finishLargetoSmall[num_vertex];
    for(int i = 0; i < num_vertex; i++){
        finishLargetoSmall[i] = i;
    }

    QuickSort(finish, 0, num_vertex - 1, finishLargetoSmall);

    cout << "finish time Large to Small:" << endl;
    PrintDataArray(finishLargetoSmall);

    gT.VariableInitializeDFS();
    int time = 0;
    for(int i = 0; i < num_vertex; i++){
        if(gT.GetColor(finishLargetoSmall[i]) == 0){
            gT.DFSVisit(finishLargetoSmall[i], time);
        }
    }

    cout << "Second DFS() on gT, finish time:\n";
    gT.PrintFinish();

    cout << "predecessor[] before SetCollapsing:\n";
    gT.PrintPredecessor();

    for (int i = 0; i< num_vertex; i++)
        gT.SetCollapsing(i);

    cout << "predecessor after SetCollapsing:\n";
    gT.PrintPredecessor();

    int num_cc = 0;
    for(int i = 0; i<num_vertex; i++){
        if(gT.GetPredecessor(i) < 0){
            cout << "SCC#" << ++num_cc << ": " << i << " ";
            for(int j = 0; j<num_vertex; j++){
                if(gT.GetPredecessor(j) == i){
                    cout << j << " ";
                }
            }
            cout << endl ;
        }
    }
    cout << endl ;
}

void Graph::VariableInitializeDFS(){
    color = new int[num_vertex];
    discover = new int[num_vertex];
    finish = new int[num_vertex];
    predecessor = new int[num_vertex];

    for(int i = 0; i < num_vertex; i++){
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }
}

Graph Graph::GraphTranspose(){
    Graph gT(num_vertex);
    for(int i = 0; i < num_vertex; i++){
        for(list<int>::iterator itr = AdjList[i].begin();
        itr != AdjList[i].end(); itr++){
            gT.AddEdgeList(*itr, i);
        }
    }
    return gT;
}

void Graph::PrintDataArray(int *array){
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << i;
    cout << endl;
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << array[i];
    cout << endl;
}
void Graph::PrintFinish(){
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << i;
    cout << endl;
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << finish[i];
    cout << endl;
}
void Graph::PrintPredecessor(){
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << i;
    cout << endl;
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << predecessor[i];
    cout << endl;
}

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
}


void Graph::SetCollapsing(int current){
    int root;
    for(root = current; predecessor[root] >= 0 ; root = predecessor[root]);

    while(current != root){
        int parent = predecessor[current];
        predecessor[current] = root;
        current = parent;
    }
}

void Graph::DFS(int Start){
    color = new int[num_vertex];
    predecessor = new int[num_vertex];
    discover = new int[num_vertex];
    finish = new int[num_vertex];

    int time = 0;
    for(int i = 0; i < num_vertex; i++){
        color[i] = 0;
        predecessor[i] = -1;
        discover[i] = 0;
        finish[i] = 0;
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
            DFSVisit(*itr, time);
        }
    }
    color[vertex] = 2;
    finish[vertex] = ++time;
}

void Graph::BFS(int Start){
    color = new int[num_vertex];
    predecessor = new int[num_vertex];
    distance = new int[num_vertex];

    for(int i = 0; i < num_vertex; i++){
        color[i] = 0;
        predecessor[i] = -1;
        distance[i] = num_vertex + 1;
    }

    queue<int> q;
    int i = Start;

    for(int j = 0; j < num_vertex; j++){
        if(color == 0){
            color[i] = 1;
            distance[i] = 0;
            predecessor[i] = -1;
            
            q.push(i);

            while(!q.empty()){
                int u = q.front();
                for(list<int>::iterator itr = AdjList[u].begin(); 
                itr != AdjList[u].end(); itr++){
                    if(color[i] == 0){
                        color[*itr] = 1;
                        distance[*itr] = distance[u]+1;
                        predecessor[*itr] = u;
                        q.push(*itr); 
                    }
                }
                q.pop();
                color[u] = 2;
            }
        }
        i = j;
    }
}


int main(){
    Graph g4(9);
    g4.AddEdgeList(0, 1);
    g4.AddEdgeList(1, 2);g4.AddEdgeList(1, 4);
    g4.AddEdgeList(2, 0);g4.AddEdgeList(2, 3);g4.AddEdgeList(2, 5);
    g4.AddEdgeList(3, 2);
    g4.AddEdgeList(4, 5);g4.AddEdgeList(4, 6);
    g4.AddEdgeList(5, 4);g4.AddEdgeList(5, 6);g4.AddEdgeList(5, 7);
    g4.AddEdgeList(6, 7);
    g4.AddEdgeList(7, 8);
    g4.AddEdgeList(8, 6);

    cout << "Vertex(0) as starting point for the First DFS():\n\n";
    g4.PrintSCCs();
    cout << "Vertex(3) as starting point for the First DFS():\n\n";
    g4.PrintSCCs(3);


    return 0;
}