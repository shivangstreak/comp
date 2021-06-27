#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=4*1e5+5;
ll arr[N];
bitset<N> vis;
map<ll,ll>mymap;
int main(){
	faster;
	int n,k;cin>>n>>k;
	for(int i=0;i<n;i++)
		cin>>arr[i];
	int i=0,j=0;
	ll sum=0;
	while(j<n && i<n){
		while(j<n){
			if(vis[j]==0){
				mymap[arr[j]]++;
				vis[j]=1;	
			}
			if(mymap[arr[j]]>=k){
				//cout<<j<<" ";
				sum+=n-j;
				break;
			}
			j++;	
		}
		mymap[arr[i]]--;
		i++;
	}	
	cout<<sum<<"\n";
	return 0;
}
