#include<iostream>

#define ll long long
#define endl '\n'

using namespace std;

struct ma{
    int max,index;
};

void MaxHeapify(int arr[],int index,int size){
    if(index*2+1==size){
        if(arr[index]<arr[index*2])swap(arr[index],arr[index*2]);
    }else if(index*2!=size&&index*2+1!=size){
        ma max;
        if(arr[index*2]>arr[index*2+1]){
            max.max=arr[index*2];
            max.index=index*2;
        }else{
            max.max=arr[index*2+1];
            max.index=index*2+1;
        }
        if(arr[index]<max.max)swap(arr[index],arr[max.index]);
    }
    cout<<index<<" "<<size<<" "<<arr[index]<<" "<<arr[index*2]<<" "<<arr[index*2+1]<<endl;
}
void BuildMaxHeap(int arr[],int index,int size){
    for(int i=size/2;i>=1;i--){
        MaxHeapify(arr,i,size);
    }
}

int main(){
    int arr[10] = {'\0',9,7,8,6,4,2,3,5,1};
    int size = 9;
    for(int i=1;i<10;i++){
        swap(arr[1],arr[size]);
        BuildMaxHeap(arr,1,size--);
    }
    for(int i=1;i<10;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    return 0;
}