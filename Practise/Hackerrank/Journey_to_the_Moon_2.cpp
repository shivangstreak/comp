#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
vector<int>g[N];
bitset<N>vis;
ll res[N];
ll dfs(int s){
	vis[s]=1;
	ll d=0;
	int si=g[s].size();
	for(int i=0;i<si;i++){
		if(vis[g[s][i]]==0){
			d+=dfs(g[s][i]);
		}
	}
	return d+1;
}
int main(){
	int a,b,n,m;scanf("%d%d",&n,&m);
	vis.reset();
	while(m--){
		scanf("%d%d",&a,&b);
		g[a].pb(b);
		g[b].pb(a);
	}
	int c=0;
	ll temp;
	ll sum=0;
	for(int i=0;i<n;i++){
		if(vis[i]==0){
			temp=dfs(i);
			res[c++]=temp;
		}	
	}
	ll same=0;
	for(int i=0;i<c;i++){
		same+=(res[i]*(res[i]-1))/2;
	}
	printf("%lld\n",(n*(n-1)/2)-same);
	return 0;
}
