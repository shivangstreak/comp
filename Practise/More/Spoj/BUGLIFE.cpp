#include<bits/stdc++.h> // Checking if Graph is Bipartite or not ...
using namespace std;
int n,q,a,b;
vector<int>g[2005];
int color[2005];
bool vis[2005];
void isBipartite(){
	int flag=0;
	for(int i=1;i<=n;i++){
		if(vis[i]==false){
			queue<int>q;
                	q.push(i);
			color[i]=1;
			while(q.empty()==false){
				int top=q.front();
				q.pop();
				for(auto x:g[top]){
					if(color[x]==-1){
						color[x]=!color[top]; //OR 1-color[top] as color can be 0 or 1
					}
					else if(color[x]==color[top]){
						flag=1;
						break;
					}
					if(vis[x]==false){
						q.push(x);
					}
				}
				if(flag==1){
					break;
				}
				vis[top]=true;
			}
		}
	}
	if(flag==1){
		printf("Suspicious bugs found!\n");
		}		
	else{
		printf("No suspicious bugs found!\n");
	}
}
int main(){
	int t;scanf("%d",&t);
	for(int k=1;k<=t;k++){
		for(int i=0;i<2005;i++){
			g[i].clear();
		}
		memset(vis,false,sizeof(vis));
		memset(color,-1,sizeof(color));
		scanf("%d%d",&n,&q);
		while(q--){
			scanf("%d%d",&a,&b);
			g[a].push_back(b);
			g[b].push_back(a);
		}
		printf("Scenario #%d:\n",k);	
		isBipartite();
	}
	return 0;
}
