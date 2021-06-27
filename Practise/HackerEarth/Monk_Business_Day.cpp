#include<bits/stdc++.h>
using namespace std;
int n,e,a,b,w;
struct edge{
	int src,dest,w;
};
vector<edge>Edge;
int dist[100004];
const int lim=1000000000;
int flag,flag3;
bool bellman_ford(int start){
	for(int i=1;i<=n;i++){
		dist[i]=lim;
	}
	dist[start]=0;
	for(int i=0;i<n-1;i++){
		for(int j=0;j<e;j++){
			int u=Edge[j].src;
			int v=Edge[j].dest;
			int weight=Edge[j].w;
			if(dist[u]!=lim && dist[u]+weight<dist[v]){
				dist[v]=dist[u]+weight;
			}
		}		
	}
	int flag2=0;
		for(int j=0;j<e;j++){
			int u=Edge[j].src;
			int v=Edge[j].dest;
			int weight=Edge[j].w;
			if(dist[u]!=lim && dist[u]+weight<dist[v]){
				flag2=1;
				dist[v]=dist[u]+weight;
				break;
			}
		}		
	if(flag2==1){
		return true;
	}
	else{
		return false;
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		flag=0;
		flag3=0;
		scanf("%d%d",&n,&e);
		Edge.clear();
		Edge.resize(e);
		for(int i=0;i<e;i++){
			scanf("%d%d%d",&a,&b,&w);
			if(a==b && w>0){
				flag3=1;
			}
			Edge[i].src=a;		
			Edge[i].dest=b;
			Edge[i].w=-1*w;
		
		}
		if(flag3==1){
			printf("Yes\n");
			continue;
		}
		if(bellman_ford(1)==true){
			printf("Yes\n");
		}
		else{
			printf("No\n");
		}	
	}
	return 0;
}
