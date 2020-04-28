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
    vector<list<int> > AdjList;
    int *color,             // 0:white, 1:gray, 2:black
        *predecessor,
        *discover,
        *finish;
public:
    Graph():num_vertex(0){};
    Graph(int N):num_vertex(N){
        // initialize Adj List
        AdjList.resize(num_vertex);
    };
    void AddEdgeList(int from, int to);
    void DFS(int Start);
    void DFSVisit(int vertex, int &time);
};

void Graph::AddEdgeList(int from, int to){
    AdjList[from].push_back(to);
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
    cout << "predecessor:" << endl;         // 印出 A(0) ~ H(7)的predecessor
    for (int i = 0; i < num_vertex; i++){
        cout << setw(4) << i;
    }
    cout << endl;
    for (int i = 0; i < num_vertex; i++){
        cout << setw(4) << predecessor[i];
    }
    cout << "\ndiscover time:" << endl;  // 印出 A(0) ~ H(7)的discover time
    for (int i = 0; i < num_vertex; i++){
        cout << setw(4) << i;
    }
    cout << endl;
    for (int i = 0; i < num_vertex; i++){
        cout << setw(4) << discover[i];
    }
    cout << "\nfinish time:" << endl;    // 印出 A(0) ~ H(7)的finish time
    for (int i = 0; i < num_vertex; i++){
        cout << setw(4) << i;
    }
    cout << endl;
    for (int i = 0; i < num_vertex; i++){
        cout << setw(4) << finish[i];
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


int main(){
    // 定義一個具有八個vertex的Graph
    Graph g2(8);
    // 建立如圖三之Graph
    g2.AddEdgeList(0, 1);g2.AddEdgeList(0, 2); 
    g2.AddEdgeList(1, 3);
    g2.AddEdgeList(2, 1);g2.AddEdgeList(2, 5);
    g2.AddEdgeList(3, 4);g2.AddEdgeList(3, 5);
    // AdjList[4] is empty
    g2.AddEdgeList(5, 1);
    g2.AddEdgeList(6, 4);g2.AddEdgeList(6, 7);
    g2.AddEdgeList(7, 6);

    g2.DFS(0);    // 以vertex(0), 也就是vertex(A作為DFS()的起點


    return 0;
}