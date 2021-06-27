/*For BFS twice 
*	In first bfs you have to find maximum length of node from root or any other internal node(does't matter which) 
*	then in second bfs consider that node as root and find maximum 
*	distance from that .That will be our answer.
*/
#include<bits/stdc++.h>
using namespace std;
#define mx 10000
vector< pair<int,int> >g[mx+5];
bool vis[mx+5];
int W[mx+5];
void bfs(int i){
	queue<pair<int,int>>q;
	q.push(make_pair(i,0));
	while(q.empty()==false){
		int val=q.front().first;
		int wt=q.front().second;
		vis[val]=true;
		//cout<<val<<" "<<wt<<endl;
		int len=g[val].size();
		for(int j=0;j<len;j++){
			if(vis[g[val][j].first]==false){
				q.push(make_pair(g[val][j].first,wt+1));
			}
		}
		W[val]=wt;
		q.pop();
	}
}
int main(){
	memset(vis,false,sizeof(vis));
	memset(W,0,sizeof(W));
	int n;scanf("%d",&n);
	for(int i=0;i<n-1;i++){
		int a,b;cin>>a>>b;
		g[a].push_back(make_pair(b,0));
		g[b].push_back(make_pair(a,0));
	}
	bfs(1);
	int o=INT_MIN,root2;
	for(int i=1;i<=n;i++){
		if(o<W[i]){
			o=W[i];
			root2=i;
		}
	}
	//cout<<root2<<endl;
	memset(vis,false,sizeof(vis));
	memset(W,0,sizeof(W));
	bfs(root2);
	o=INT_MIN;
	for(int i=1;i<=n;i++){
		if(o<W[i]){
			o=W[i];
		}
	}		
	cout<<o<<"\n";
	return 0;
}
