#include<bits/stdc++.h>
using namespace std;
int n,m,a,w,b,A,K,q;
vector<pair<int,int>>g[100004];
int dist[100004];
void dijkstra(int start){
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> >q;
	dist[start] = 0;
	q.push(make_pair(dist[start],start));
	while(q.empty()==false){
		int v=q.top().second;
		int d=q.top().first;
		q.pop();
		if(dist[v]<d){
			continue;		
		}
		dist[v]=d;
		for(int i=0;i<g[v].size(); i++){
			int v1=g[v][i].first;
			d=g[v][i].second;
	            if(dist[v1]>dist[v]+d){
        	    	dist[v1] = dist[v]+d;
        	    	q.push(make_pair(dist[v1],v1));
        	    }		
		}
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);	
		for(int i=0;i<100004;i++){
			g[i].clear();
		}
		for(int i=1;i<=n;i++){
			dist[i]=INT_MAX;	
		}
		while(m--){
			scanf("%d%d%d",&a,&b,&w);
			g[a].push_back(make_pair(b,w));
			g[b].push_back(make_pair(a,w));
		}
		dijkstra(1);
		/*for(int i=1;i<=n;i++){
			cout<<dist[i]<<" ";	
		}
		cout<<endl;*/
		scanf("%d",&q);
		while(q--){
			scanf("%d%d",&A,&K);
			printf("%d\n",max(0,K-(2*dist[A])));			
		}
	}
	return 0;
}
