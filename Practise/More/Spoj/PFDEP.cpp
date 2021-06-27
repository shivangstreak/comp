#include<bits/stdc++.h>  // Indegree Method For Topological Sorting
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int in[105];
vector<int>g[105];
vector<int>res;
set<int>Set;
void topo(){
	while(Set.empty()==false){
		int u=*(Set.begin());
		res.pb(u);
		Set.erase(Set.begin());
		int size=g[u].size();
		for(int i=0;i<size;i++){
			in[g[u][i]]--;
			if(in[g[u][i]]==0)
				Set.insert(g[u][i]);
		}
	}
}
int main(){
	int n,m,a,k,t;
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d",&t,&k);
		in[t]+=k;		
		for(int i=0;i<k;i++){
			scanf("%d",&a);
			g[a].pb(t);
		}
	}
	for(int i=1;i<=n;i++){
		if(in[i]==0)
			Set.insert(i);
	}
	topo();
	for(int i=0;i<n;i++)
		printf("%d ",res[i]);	
	printf("\n");
	return 0;
}
