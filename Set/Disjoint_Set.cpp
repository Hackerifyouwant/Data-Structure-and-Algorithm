#include<iomanip>
#include<iostream>

#define ll long long
#define endl '\n'

using namespace std;

int FindSetCollapsing(int *subset, int i){
    int root;
    for(root = i; subset[root] >= 0; root = subset[root])

    while(i != root){
        int parent = subset[i];
        subset[i] = root;
        i = parent;
    }

    return root;
}

void UnionSet(int *subset, int x, int y){
    int xroot = FindSetCollapsing(subset, x),
        yroot = FindSetCollapsing(subset, y);

    if(subset[xroot] <= subset[yroot]){
        subset[xroot] += subset[yroot];
        subset[yroot] = xroot;
    }else{
        subset[yroot] += subset[xroot];
        subset[xroot] = yroot;
    }
}

void PrintArray(int *array, int size){

    for (int i = 0; i < size; i++){   
        cout << setw(3) << i;
    }
    cout << endl;
    for (int i = 0; i < size; i++){   
        cout << setw(3) << array[i];
    }
    cout << endl;
}


int main(){
    const int size = 6;
    int array[size] = {-1, -1, -1, -1, -1, -1};
    PrintArray(array, size);

    UnionSet(array, 1, 2);
    cout << "After union(1,2):\n";
    PrintArray(array, size);

    UnionSet(array, 0, 2);
    cout << "After union(0,2):\n";
    PrintArray(array, size);

    UnionSet(array, 3, 5);
    cout << "After union(3,5):\n";
    PrintArray(array, size);

    UnionSet(array, 2, 5);
    cout << "After union(2,5):\n";
    PrintArray(array, size);


    cout << "element(5) belongs to Set(" << FindSetCollapsing(array, 5) << ").\n";
    cout << "After collapsing:\n";
    PrintArray(array, size);

}