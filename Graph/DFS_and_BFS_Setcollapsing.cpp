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
    void AddEdgeList(int from, int to);
    void BFS(int Start);    
    void DFS(int Start);
    void DFSVisit(int vertex, int &time);

    void CCDFS(int vertex);                // 利用DFS 
    void CCBFS(int vertex = 0);            // 利用BFS, 兩者邏輯完全相同
    void SetCollapsing(int vertex);
    void PrintPredecessor();               // 印出predecessor, 供驗証用, 非必要
};

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
        if(color[i] == 0){
            color[i] = 1;
            distance[i] = 0;
            predecessor[i] = -1;
            q.push(i);
            while(!q.empty()){
                int u = q.front();
                for(list<int>::iterator itr = AdjList[u].begin(); 
                itr != AdjList[u].end(); itr++){
                    if(color[*itr] == 0){
                        color[*itr] = 1;
                        predecessor[*itr] = u;
                        distance[*itr] = distance[u]+1;
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

void Graph::DFS(int Start){
    color = new int[num_vertex];           // 配置記憶體位置
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
            DFSVisit(*itr, time);
        }
    }
    color[vertex] = 2;
    finish[vertex] = ++time;
}

void Graph::SetCollapsing(int current){
    int root;
    for(root = current; predecessor[root] >= 0; root = predecessor[root]);
    
    while(current != root) {
        int parent = predecessor[current];           
        predecessor[current] = root;
        current = parent;
    }   
}

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
}

void Graph::CCDFS(int vertex = 0){
    DFS(vertex);
    PrintPredecessor();
    for(int i = 0; i < num_vertex; i++){
        SetCollapsing(i);
    }
    PrintPredecessor();

    int num_cc = 0;
    for(int i = 0; i < num_vertex; i++){
        if(predecessor[i] < 0){
            cout << "Component#" << ++num_cc << ": " << i << " ";
            for(int j = 0;j < num_vertex; j++){
                if(predecessor[j] == i){
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }
}

void Graph::CCBFS(int vertex){
    
    BFS(vertex);
    PrintPredecessor();
    for(int i = 0; i < num_vertex; i++){
        SetCollapsing(i);
    }
    PrintPredecessor();

    int num_cc = 0;
    for(int i = 0; i < num_vertex; i++){
        if(predecessor[i] < 0){
            cout << "Component#" << ++num_cc << ": " << i << " ";
            for(int j = 0;j < num_vertex; j++){
                if(predecessor[j] == i){
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }
}

void Graph::PrintPredecessor(){
    cout << "predecessor:" << endl;
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << i;
    cout << endl;
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << predecessor[i];
    cout << endl;
}

int main(){
    Graph g3(9);
    g3.AddEdgeList(0, 1);
    g3.AddEdgeList(1, 0);g3.AddEdgeList(1, 4);g3.AddEdgeList(1, 5);
    // AdjList[2] empty
    g3.AddEdgeList(3, 6);
    g3.AddEdgeList(4, 1);g3.AddEdgeList(4, 5);
    g3.AddEdgeList(5, 1);g3.AddEdgeList(5, 4);g3.AddEdgeList(5, 7);
    g3.AddEdgeList(6, 3);g3.AddEdgeList(6, 8);
    g3.AddEdgeList(7, 5);
    g3.AddEdgeList(8, 6);

    g3.CCDFS();
    cout << endl;
    g3.CCBFS();
    cout << endl;


    return 0;
}