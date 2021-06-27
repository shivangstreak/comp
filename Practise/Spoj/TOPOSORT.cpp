#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=10005;
int in[N];
vector<int>ans;
vector<int>g[N];
set<int>Set;
void topo(){
	int u,v;
	while(Set.empty()==false){
		u=*(Set.begin());
		ans.pb(u);
		Set.erase(Set.begin());
		int size=g[u].size();
		for(int i=0;i<size;i++){
			v=g[u][i];
			in[v]--;
			if(in[v]==0){
				Set.insert(v);
			}
		}
	}
}
int main(){
	int n,m,x,y;scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d",&x,&y);
		g[x].pb(y);
		in[y]++;
	}
	for(int i=1;i<=n;i++)
		if(in[i]==0){
			Set.insert(i);
		}	
	topo();		
	if(ans.size()!=n){
		printf("Sandro fails.\n");
	}
	else{
		for(int i=0;i<n;i++)
			printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}
