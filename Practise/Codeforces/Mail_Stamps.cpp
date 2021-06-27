#include<bits/stdc++.h>
using namespace std;
#define ll long long
map<ll,vector<ll>>g;
map<ll,bool>vis;
vector<ll>result;
void dfs(ll start){
	vis[start]=true;
	result.push_back(start);
	for(auto x:g[start]){
		if(vis[x]==false){
			dfs(x);
		}
	}
}
int main(){	
	int n;scanf("%d",&n);
	ll a,b;
	for(int i=0;i<n;i++){
		scanf("%lld%lld",&a,&b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	ll start;
	for(auto x:g){
		if(x.second.size()==1){
			start=x.first;
			break;
		}
	}
	dfs(start);
	for(auto x:result){
		cout<<x<<" ";
	}
	printf("\n");
	return 0;
}
