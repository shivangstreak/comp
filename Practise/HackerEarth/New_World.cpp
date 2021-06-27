#include<bits/stdc++.h> // Binary Search
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
int t,n,k;
int arr[N];
bool chk(int D){
	int current=0,prev=0,requ=0;
	for(int i=0;i<n;i++){
		while(current<n && arr[current]-arr[prev]<=D){
			current++;
		}
		requ++;
		if(current==n)
			break;
		prev=current-1;	
	}
	if(current!=n){
		return false;
	}
	if(requ<=k){
		return true;	
	}
	else{
		return false;
	}
}
int main(){
	scanf("%d",&t);
	int start,end;
	while(t--){
		scanf("%d%d",&n,&k);
		start=0;
		end=1e9+5;
		for(int i=0;i<n;i++){
			scanf("%d",&arr[i]);
		}
		int pos;
		while(start<=end){
			int mid=(start+end)>>1;
			if(chk(mid)==true){
				pos=mid;
				end=mid-1;
			}
			else{
				start=mid+1;
			}
		}
		printf("%d\n",pos);		
	}
	return 0;
}	
