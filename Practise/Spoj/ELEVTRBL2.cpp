#include<bits/stdc++.h>
using namespace std;
const int mx=1000005;
int f,s,g,u,d;
int dist[mx];
bool vis[mx];
void bfs(){
	queue<int>q;
	dist[s]=0;
	q.push(s);
	while(q.empty()==false){
		int top=q.front();
		q.pop();
		int UP=top+u;
		int down=top-d;
		if(UP<=f && vis[UP]==false){
			dist[UP]=dist[top]+1;
			vis[UP]=true;
			q.push(UP);
		}
		if(down>=1 && vis[down]==false){
			dist[down]=dist[top]+1;
			vis[down]=true;
			q.push(down);
		}	
	}
}
int main(){
	scanf("%d%d%d%d%d",&f,&s,&g,&u,&d);
	memset(dist,0,sizeof(dist));
	dist[g]=-1;
	memset(vis,false,sizeof(vis));
	if(s==g){
		cout<<"0\n";
		return 0;		
	}
	bfs();
	if(dist[g]==-1){
		printf("use the stairs\n");
	}
	else{
		printf("%d\n",dist[g]);
	}
	return 0;
}
