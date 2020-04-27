#include<iostream>
#include<vector>
#include<list>
#include<utility>
#include<iomanip>

#define Max_Distance 100 
#define ll long long
#define endl '\n'

using namespace std;

class Graph_SP{
private:
    int num_vertex;
    vector<list <pair<int, int> > >Adjlist;
    vector<int> predecessor,distance;
public:
    Graph_SP():num_vertex(0){};
    Graph_SP(int n):num_vertex(n){
        Adjlist.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void PrintDataArray(vector<int> array);

    void InitializeSingleSource(int Start);
    void Relax(int X, int Y, int weight);
    bool BellmanFord(int Start = 0); 
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
    cout << endl << endl;
}

void Graph_SP::InitializeSingleSource(int Start){
    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for(int i = 0; i < num_vertex; i++){
        distance[i] = Max_Distance;
        predecessor[i] = -1;
    }
    distance[Start] = 0;
}

void Graph_SP::Relax(int from, int to, int weight){
    if(distance[from]+ weight < distance[to]){
        distance[to] = distance[from] + weight;
        predecessor[to] = from;
    }
}

bool Graph_SP::BellmanFord(int Start){
    InitializeSingleSource(Start);

    for(int i = 0; i < num_vertex - 1; i++){
        for(int j = 0; j < num_vertex; j++){
            for(list<pair<int,int> >::iterator itr = Adjlist[j].begin();
            itr != Adjlist[j].end(); itr++){
                Relax(j, itr->first, itr->second);
            }
        }
    }

    for(int i = 0; i < num_vertex; i++){
        for(list<pair<int,int> >::iterator itr = Adjlist[i].begin();
        itr != Adjlist[i].end(); itr++){
            if(distance[itr->first] > distance[i] + itr->second){
                return false;
            }
        }
    }
    cout << "predecessor[]:\n";
    PrintDataArray(predecessor);
    cout << "distance[]:\n";
    PrintDataArray(distance);

    return true;   
}

int main(){
    Graph_SP g7(6);
    g7.AddEdge(0, 1, 5);
    g7.AddEdge(1, 4, -4);g7.AddEdge(1, 2, 6);
    g7.AddEdge(2, 4, -3);g7.AddEdge(2, 5, -2);
    g7.AddEdge(3, 2, 4);
    g7.AddEdge(4, 3, 1);g7.AddEdge(4, 5, 6);
    g7.AddEdge(5, 0, 3);g7.AddEdge(5, 1, 7);

    if (g7.BellmanFord(0))
        cout << "There is no negative cycle.\n";
    else
        cout << "There is negative cycle.\n";


    return 0;
}