#include<iostream>
#include<iomanip>
#include<vector>
#include<list>
#include<utility>

#define MAX_Distance 100
#define ll long long
#define endl '\n'

using namespace std;

class Graph_SP{
private:
    int num_vertex;
    vector<list<pair<int,int> > >Adjlist;
    vector<int> predecessor,distance;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        Adjlist.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void PrintDataArray(vector<int> array);
    void PrintIntArray(int *array);

    void InitializeSingleSource(int Start);
    void Relax(int X, int Y, int weight);

    void DAG_SP(int Start = 0);
    void GetTopologicalSort(int *array, int Start);
    void DFSVisit_TS(int *array, int *color, int *discover, 
    int *finish, int vertex, int &time, int &count);
};

void Graph_SP::AddEdge(int from, int to, int weight){
    Adjlist[from].push_back(make_pair(to, weight));
}

void Graph_SP::PrintDataArray(vector<int> array){
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << i;
    cout << endl;
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << array[i];
    cout << endl;
}

void Graph_SP::PrintIntArray(int *array){
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << i;
    cout << endl;
    for (int i = 0; i < num_vertex; i++)
        cout << setw(4) << array[i];
    cout << endl;
}

void Graph_SP::InitializeSingleSource(int Start){
    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for(int i = 0; i < num_vertex; i++){
        distance[i] = MAX_Distance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;
}

void Graph_SP::Relax(int from, int to, int weight){
    if(distance[to] > distance[from] + weight){
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}

void Graph_SP::DAG_SP(int Start){
    InitializeSingleSource(Start);

    int topologicalsort[num_vertex];
    GetTopologicalSort(topologicalsort, Start);

    for(int i = 0; i < num_vertex; i++){
        int v = topologicalsort[i];
        for(list<pair<int,int> >::iterator itr = Adjlist[v].begin();
        itr != Adjlist[v].end(); itr++){
            Relax(v, itr->first, itr->second);
        }
    }
    cout << "\nprint predecessor:\n";
    PrintDataArray(predecessor);
    cout << "\nprint distance:\n";
    PrintDataArray(distance);
}

void Graph_SP::GetTopologicalSort(int *array, int Start){
    int color[num_vertex] , discover[num_vertex], finish[num_vertex];

    for(int i = 0; i < num_vertex; i++){
        color[i] = 0;
        discover[i] = 0;
        finish[i] = 0;
        predecessor[i] = -1;
    }

    int time = 0,
        count = num_vertex - 1,
        i = Start;
    for(int j = 0; j < num_vertex; j++){
        if(color[i] == 0){
            DFSVisit_TS(array, color, discover, finish, i , time, count);
        }
        i = j;
    }
    cout << "\nprint discover time:\n";
    PrintIntArray(discover);
    cout << "\nprint finish time:\n";
    PrintIntArray(finish);
}
void Graph_SP::DFSVisit_TS(int *array, int *color, int *discover,
                           int *finish, int vertex, int &time, int &count){
    color[vertex] = 1;
    discover[vertex] = ++time;
    for(list<pair<int,int> >::iterator itr = Adjlist[vertex].begin();
    itr != Adjlist[vertex].end(); itr++){
        if(color[itr->first] == 0){
            predecessor[itr->first] = vertex;
            DFSVisit_TS(array, color, discover, finish, itr->first, time, count);
        }
    }
    color[vertex] = 2;
    finish[vertex] = ++time;
    array[count--] = vertex;
}
int main(){
     Graph_SP g8(7);
    g8.AddEdge(0, 1, 3);g8.AddEdge(0, 2, -2);
    g8.AddEdge(1, 3, -4);g8.AddEdge(1, 4, 4);
    g8.AddEdge(2, 4, 5);g8.AddEdge(2, 5, 6);
    g8.AddEdge(3, 5, 8);g8.AddEdge(3, 6, 2);
    g8.AddEdge(4, 3, -3);g8.AddEdge(4, 6, -2);
    g8.AddEdge(5, 6, 2);

    g8.DAG_SP(0);        // 以vertex(0)作為起點
    g8.DAG_SP(2);


    return 0;
}