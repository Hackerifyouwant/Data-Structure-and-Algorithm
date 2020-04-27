#include<iostream>
#include<vector>

#define ll long long
#define endl '\n'

using namespace std;

void insertionsort(vector<int> &arr){
    for(int i=0;i<arr.size();i++){
        int j = i - 1;
        int key = arr[i];
        while(j >= 0 & key < arr[j]) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

int main(){
    int arr[] = {7,6,5,4,3,2,1,0};
    vector<int> v(arr,arr+sizeof(arr)/sizeof(int));
    insertionsort(v);
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}