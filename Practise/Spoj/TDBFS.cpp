#include<bits/stdc++.h>
using namespace std;
vector<int>g[1005];
bool vis[1005];
void dfs(int n){
	vis[n]=true;
	printf("%d ",n);
	int len=g[n].size();
	for(int i=0;i<len;i++){
		if(vis[g[n][i]]==false){
			dfs(g[n][i]);
		}
	}	
}
void bfs(int n){
	queue<int>s;
	s.push(n);
	while(s.empty()==false){
		int top=s.front();
		s.pop();
		if(vis[top]==true)
			continue;
		vis[top]=true;
		printf("%d ",top);
		int len=g[top].size();
		for(int i=0;i<len;i++){
			if(vis[g[top][i]]==false){
				s.push(g[top][i]);
			}
		}
	}
	printf("\n");	
}
int main(){
	int t;scanf("%d",&t);
	for(int w=1;w<=t;w++){
		for(int i=0;i<1005;i++){
			g[i].clear();
		}
		memset(vis,false,sizeof(vis));
		int n;scanf("%d",&n);
		int n1=n;
		while(n1--){
			int a,q;scanf("%d%d",&a,&q);
			while(q--){
				int b;scanf("%d",&b);
				g[a].push_back(b);
			}
		}
		int x,y;scanf("%d%d",&x,&y);
		printf("graph %d\n",w);
		while(!(x==0 && y==0)){
			memset(vis,false,sizeof(vis));
			if(y==1){
				bfs(x);
			}
			else{
				dfs(x);
				printf("\n");
			}
			scanf("%d%d",&x,&y);
		}		
	}
	return 0;
}
