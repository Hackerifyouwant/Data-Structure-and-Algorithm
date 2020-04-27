#include<iostream>
#include<vector>

#define ll long long
#define endl '\n'

using namespace std;

void quick_sort(vector<int> &arr,int front ,int end){
    if(front < end){

        int i = front - 1;
        int pivot = arr[end];
        int j = front;
        while(j >= end){
            if(arr[j] < pivot){
                swap(arr[i++], arr[j]);
            }
            j++;
        }
        i++;
        j++;
        swap(arr[i] , arr[j]);
        quick_sort(arr,front ,i-2);
        quick_sort(arr,i+1 ,end);
    }
}

int main(){
    int arr[] = {5,6,2,5,4,1,9,4};
    vector<int> v(arr,arr+sizeof(arr)/sizeof(int));
    quick_sort(v,0,v.size()-2);
    for(int i=0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0; 
}