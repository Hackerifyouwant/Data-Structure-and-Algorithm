#include<iostream>
#include<vector>
#include<iomanip>

#define MaxDistance 1000
#define ll long long
#define endl '\n'

using namespace std;

class Graph_SP_AllPairs{
private:
    int num_vertex;
    vector<vector<int> >AdjMartix, Distance, Predecessor;
public:
    Graph_SP_AllPairs():num_vertex(0){};
    Graph_SP_AllPairs(int n);
    void AddEdge(int from, int to, int weight);
    void PrintData(vector<vector<int> >array);
    void InitializeData();
    void FloydWarshall();
};

Graph_SP_AllPairs::Graph_SP_AllPairs(int n):num_vertex(n){
    AdjMartix.resize(num_vertex);

    for(int i = 0; i < num_vertex; i++){
        AdjMartix[i].resize(num_vertex, MaxDistance);
        for(int j = 0; j < num_vertex; j++){
            if(i == j){
                AdjMartix[i][j] = 0;
            }
        }
    }
}

void Graph_SP_AllPairs::InitializeData(){
    Distance.resize(num_vertex);
    Predecessor.resize(num_vertex);

    for(int i = 0; i < num_vertex; i++){
        Distance[i].resize(num_vertex);
        Predecessor[i].resize(num_vertex, -1);
        for(int j = 0; j < num_vertex; j++){
            Distance[i][j] = AdjMartix[i][j];
            if(Distance[i][j] != 0 && Distance[i][j] != MaxDistance){
                Predecessor[i][j] = i;
            }
        }
    }
}

void Graph_SP_AllPairs::FloydWarshall(){
    InitializeData();

    cout << "initial Distance[]:\n";
    PrintData(Distance);
    cout << "\ninitial Predecessor[]:\n";
    PrintData(Predecessor);

    for(int k = 0; k < num_vertex; k++){
        cout << "\nincluding vertex(" << k << "):\n";
        for(int i = 0; i < num_vertex; i++){
            for(int j = 0; j < num_vertex; j++){
                if((Distance[i][j] > Distance[i][k] + Distance[k][j]) 
                    && (Distance[i][k] != MaxDistance)){
                    Distance[i][j] = Distance[i][k] + Distance[k][j];
                    Predecessor[i][j] = Predecessor[k][j];
                }
            }
        }
        cout << "Distance[]:\n";
        PrintData(Distance);
        cout << "\nPredecessor[]:\n";
        PrintData(Predecessor);
    }

}

void Graph_SP_AllPairs::PrintData(vector< std::vector<int> > array){

    for (int i = 0; i < num_vertex; i++){
        for (int j = 0; j < num_vertex; j++) {
            std::cout << setw(5) << array[i][j];
        }
        std::cout << endl;
    }
}

void Graph_SP_AllPairs::AddEdge(int from, int to, int weight){
    AdjMartix[from][to] = weight;
}

int main(){
    Graph_SP_AllPairs g10(4);
    g10.AddEdge(0, 1, 2);g10.AddEdge(0, 2, 6);g10.AddEdge(0, 3, 8);
    g10.AddEdge(1, 2, -2);g10.AddEdge(1, 3, 3);
    g10.AddEdge(2, 0, 4);g10.AddEdge(2, 3, 1);

    g10.FloydWarshall();

    return 0;
}