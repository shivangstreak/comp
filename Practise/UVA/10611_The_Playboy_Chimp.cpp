#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[50005];
int key;
int aux_indx;
int Binary_search(int start,int end){
	int mid;
	while(start<=end){
		mid=(start+end)>>1;
		if(key==arr[mid]){
			return mid;
		}
		else if(key>arr[mid]){
			start=mid+1;
		}
		else{
			end=mid-1;
		}
	}
	aux_indx=ceil(double(start+end)/2.0);
	return -1;
}
int main(){
	int n,q,d;cin>>n;
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	cin>>q;
	while(q--){
		cin>>d;
		key=d-1;
		int u=Binary_search(0,n-1);
		if(u!=-1){
			cout<<arr[u];
		}
		else if(aux_indx-1>=0){
			cout<<arr[aux_indx-1];		
		}
		else{
			cout<<"X";
		}
		cout<<" ";
		key=d+1;
		u=Binary_search(0,n-1);
		if(u!=-1){
			cout<<arr[u];
		}
		else if(aux_indx<n){
			cout<<arr[aux_indx];
		}
		else{
			cout<<"X";
		}
		cout<<"\n";		
	}
	return 0;
}
