#include<bits/stdc++.h>
using namespace std;
int parent[100005];
int dist[100005];
vector<int>g[100005];
vector<int>cost[100005];
struct node{
	int parent;
	int i;
	int w;
};
class cmp{
	public:
		bool operator()(const struct node &t1,const struct node &t2){
			return t1.w>t2.w;  // MinHeap on bases of w....
		}
};
void Find_path(int n){
	if(n==0){
		return;
	}
	Find_path(parent[n]);
	printf("%d ",n);
}
int main(){
	memset(parent,-1,sizeof(parent));
	int n,m;scanf("%d%d",&n,&m);
	while(m--){
		int a,b,w;scanf("%d%d%d",&a,&b,&w);
		if(a==b){
			continue;   
		}
		g[a].push_back(b);
		cost[a].push_back(w);
		g[b].push_back(a);
		cost[b].push_back(w);
	}
	priority_queue<node,vector<node>,cmp>q;
	node temp,top;
	temp.parent=0;
	temp.i=1;
	temp.w=0;
	q.push(temp);
	while(q.empty()==false){
		top=q.top();
		q.pop();
		if(parent[top.i]==-1){
			parent[top.i]=top.parent;
			int size=g[top.i].size();
			for(int k=0;k<size;k++){
				if(parent[g[top.i][k]]==-1){
					temp.i=g[top.i][k];
					temp.parent=top.i;
					temp.w=top.w+cost[top.i][k];
					q.push(temp);
				}
			}
		}
	}
	if(parent[n]==-1){
		printf("-1\n");
	}
	else{
		Find_path(n);
		printf("\n");
	}
	return 0;
}
