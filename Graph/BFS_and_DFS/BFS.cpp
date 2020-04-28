#include<iostream>
#include<queue>
#include<vector>
#include<list>

#define ll long long 
#define endl '\n'

using namespace std;

/*---------------------
queue：如同Level-Order Traversal，BFS()將使用queue來確保「先被搜尋到的vertex，就先成為新的搜尋起點」。

color array：利用color標記哪些vertex已經被「找到」，哪些還沒有。
    白色表示該vertex還沒有被找過；
    灰色表示該vertex已經被某個vertex找過；
    黑色表示該vertex已經從queue的隊伍中移除。

distance array：記錄每一個vertex與起點vertex之距離。

predecessor array：記錄某個vertex是被哪一個vertex找到的，如此便能回溯路徑。
---------------------*/
class Graph{
private:
    int num_vertex;
    vector<list<int> > Adjlist;
    int *color, *distance, *predecessor;
public:
    Graph():num_vertex(0){};
    Graph(int N):num_vertex(N){
        Adjlist.resize(num_vertex);
    }
    void AddEdgeList(int from, int to);
    void BFS(int Start);
};

void Graph::AddEdgeList(int from, int to){
    Adjlist[from].push_back(to);
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
        if(color[i] == 0){
            color[i] = 1;
            distance[i] = 0;
            predecessor[i] = -1;
            q.push(i);
            while(!q.empty()){
                int u = q.front();
                for(list<int>::iterator itr = Adjlist[u].begin();
                itr != Adjlist[u].end(); itr++)
                if(color[*itr] == 0){
                    color[*itr] = 1;
                    distance[*itr] = distance[u] + 1;
                    predecessor[*itr] = u;
                    q.push(*itr);
                }
                q.pop();
                color[u] = 2;
                cout<< u << " " << predecessor[u] << " " << distance[u] <<endl;
            }
            
        }
        i = j;
    }
}

int main(){
    Graph g1(9);    
    // 建立出圖二(a)的Adjacency List
    g1.AddEdgeList(0, 1);g1.AddEdgeList(0, 2);g1.AddEdgeList(0, 3);
    g1.AddEdgeList(1, 0);g1.AddEdgeList(1, 4);
    g1.AddEdgeList(2, 0);g1.AddEdgeList(2, 4);g1.AddEdgeList(2, 5);g1.AddEdgeList(2, 6);g1.AddEdgeList(2, 7);
    g1.AddEdgeList(3, 0);g1.AddEdgeList(3, 7);
    g1.AddEdgeList(4, 1);g1.AddEdgeList(4, 2);g1.AddEdgeList(4, 5);
    g1.AddEdgeList(5, 2);g1.AddEdgeList(5, 4);g1.AddEdgeList(5, 8);
    g1.AddEdgeList(6, 2);g1.AddEdgeList(6, 7);g1.AddEdgeList(6, 8);
    g1.AddEdgeList(7, 2);g1.AddEdgeList(7, 3);g1.AddEdgeList(7, 6);
    g1.AddEdgeList(8, 5);g1.AddEdgeList(8, 6);

    g1.BFS(0);    


    return 0;
}