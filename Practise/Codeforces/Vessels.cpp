#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=2*1e5+5;
const ll MAX=2*1e9+5;
ll arr[N],vol[N],parent[N];
ll root(ll n){
	if(parent[n]!=n){
		parent[n]=root(parent[n]);
	}
	return parent[n];
}
int main(){
	faster;
	ll n,d,l,r,m,w;
	cin>>n;
	for(int i=1;i<=n;i++){
		parent[i]=i;
		cin>>arr[i];
	}
	parent[n+1]=n+1;
	arr[n+1]=MAX;
	cin>>m;
	while(m--){
		cin>>d;
		if(d==1){
			cin>>l>>r;
			w=root(l);
			//cout<<"parent of "<<l<<" is "<<w<<endl;
			if(w==n+1){
				continue;
			}
			while(r!=0){
				//cout<<"r is "<<r<<endl;
				if(vol[w]+r>arr[w]){
					r=vol[w]+r-arr[w];
					vol[w]=arr[w];
					parent[w]=w+1;
					w++;
					if(w==n+1){
						break;
					}
				}
				else{
					vol[w]=vol[w]+r;
					r=0;
				}
			}
			//cout<<"Final parent of "<<l<<" is "<<root(l)<<endl;
		}
		else{
			cin>>l;
			cout<<vol[l]<<"\n";
		}
	}
	return 0;
}
