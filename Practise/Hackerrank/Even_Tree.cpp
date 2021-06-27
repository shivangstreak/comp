#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int>g[105];
int ans=0;
bool vis[105];
int dfs(int s){
	vis[s]=true;
	int temp=0;
	int num_of_nodes=0;
	int size=g[s].size();
	for(int i=0;i<size;i++){
		if(vis[g[s][i]]==false){
			temp=dfs(g[s][i]);
			if(temp%2==0){
				ans++;
			}	
			else{
				num_of_nodes+=temp;
			}
		}
	}
	return num_of_nodes+1;
}
int main(){
	int a,b,n,m;scanf("%d%d",&n,&m);
	memset(vis,false,sizeof(vis));
	while(m--){
		scanf("%d%d",&a,&b);
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
