#include<bits/stdc++.h>
using namespace std;
int n,m,a,w,b,A,K,q;
vector<vector<pair<int,int>>>g;
int dist[10005];
void dijkstra(int start){
	dist[start]=0;
	int c=0;
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
	q.push(make_pair(0,start));
	while(q.empty()==false){
		c++;
		pair<int,int> top=q.top();
		q.pop();
		int v=top.second;
		int d=top.first;
		if(d<=dist[v]){
			for(auto x:g[v]){
				int v2=x.second;
				int d2=x.first;
				if(dist[v2]>dist[v]+d2){
					dist[v2]=dist[v]+d2;
					q.push(make_pair(dist[v2],v2));
				}
			}
		}
		if(c==n){
			return;
		}
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);	
		g.clear();
		g.resize(n+1);
		for(int i=0;i<10005;i++){
			dist[i]=INT_MAX;	
		}
		while(m--){
			scanf("%d%d%d",&a,&b,&w);
			g[a].push_back(make_pair(w,b));
			g[b].push_back(make_pair(w,a));
		}
		int start;cin>>start;
		dijkstra(start);
		/*scanf("%d",&q);
		for(int i=1;i<=n;i++){
			cout<<i<<" "<<dist[i]<<endl;	
		}
		while(q--){
			scanf("%d%d",&A,&K);
			printf("%d\n",max(0,K-2*dist[A]));			
		}*/
	}
	return 0;
}
