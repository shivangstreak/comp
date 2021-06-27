#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=100005;
vector<int>g[N];
int in[N];
queue<int>Set;
int Prev;
int parent[N];
vector<int>ans;
void topo(){
	int u;
	while(Set.empty()==false){
		u=Set.front();
		Set.pop();
		parent[u]=Prev;
		int size=g[u].size();
		for(int i=0;i<size;i++){
			int v=g[u][i];
			in[v]--;
			if(in[v]==0){
				Set.push(v);
			}
		}
		Prev=u;
	}
}
int main(){
	int n,m,w,a;
	Prev=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&w);
		for(int j=1;j<=w;j++){
			scanf("%d",&a);
			g[i].pb(a);
			in[a]++;
		}
	}
	for(int i=1;i<=n;i++){
		if(in[i]==0){
			Set.push(i);
		}	
	}
	topo();
	for(int i=1;i<=n;i++)
		printf("%d\n",parent[i]);
	return 0;
}
