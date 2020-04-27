#include<iostream>
#include<vector>
#define MAX 1000000000000000005

#define ll long long 
#define endl '\n'

using namespace std;

void merge(vector<ll> &v,ll front ,ll mid ,ll end){
    vector<ll> leftsub(v.begin()+front,v.begin()+mid+1),
                rightsub(v.begin()+mid+1,v.begin()+end+1);
    leftsub.insert(leftsub.end(),MAX);
    rightsub.insert(rightsub.end(),MAX);
    ll idleft = 0;
    ll idright = 0;
    for(ll i = front;i <= end; i++){
        if(leftsub[idleft] <= rightsub[idright]){
            v[i] = leftsub[idleft];
            idleft++; 
        }else{
            v[i] = rightsub[idright];
            idright++;

        }
    }
    
}

void mergesort(vector<ll> &v,ll front ,ll end){
    if(front < end){
        ll mid = (front + end)/2;
        mergesort(v,front,mid);
        mergesort(v,mid+1,end);
        merge(v,front,mid,end);
    }
}


int main(){
    vector<ll> v;
    ll n;
    cin>>n;
    for(ll i;i<n;i++){
        int a;
        cin>>a;
        v.push_back(a);
    }
    mergesort(v,0,n-1);
    
    for(ll i;i<n;i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}