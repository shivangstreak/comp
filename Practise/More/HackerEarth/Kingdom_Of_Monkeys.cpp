#include<bits/stdc++.h>  // Graphs DFS....
using namespace std;
#define ll long long
map<int,vector<int>>graph;
void dfs(int i,ll &c,ll a[],bool vis[]){
	stack<int>s;
	s.push(i);
	while(s.empty()==false){
		int top=s.top();
		s.pop();
		if(vis[top]==true){
			continue;
		}		
		vis[top]=true;
		c+=a[top];
		int y=graph[top].size();
		for(int j=0;j<y;j++){
			s.push(graph[top][j]);
		}
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		graph.clear();
		int n,m;scanf("%d%d",&n,&m);
		ll a[n+1];
		bool vis[n+1];
		while(m--){
			int a,b;scanf("%d%d",&a,&b);
			graph[a].push_back(b);
			graph[b].push_back(a);
		}
		for(int i=1;i<=n;i++){
			scanf("%lld",&a[i]);
			vis[i]=false;
		}
		priority_queue<ll>q;
		for(int i=1;i<=n;i++){
			if(vis[i]==false){
				ll c=0;
				dfs(i,c,a,vis);
				q.push(c);
			}
		}
		cout<<q.top()<<"\n";
	}
	return 0;
}
