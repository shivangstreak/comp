#include<bits/stdc++.h>  // Dijkstra using adj list...and priority queue!!! also printing the path!!
using namespace std;
int n,e;
int dist[100];
bool vis[100];
int parent[100];
void Find_path(int i){
	if(i==-1){
		return;
	}
	Find_path(parent[i]);
	printf("%d ",i);
}
struct node{
	int v;
	int dist;
	node(){}
	node(int i,int d){
		v=i;
		dist=d;
	}
};
bool operator<(const node &A,const node &B){
	return A.dist>B.dist; // For minHeap
}
vector<pair<int,int>>graph[100];
int main(){
	printf("Enter numer of vertices and numer of edges resp.\n");
	cin>>n>>e;
	printf("Now enter %d edges \n",e);
	for(int i=0;i<e;i++){
		int a,b,w;
		cin>>a>>b>>w;
		graph[a].push_back(make_pair(b,w));
		graph[b].push_back(make_pair(a,w));
	}
	printf("Enter source\n");
	int src;cin>>src;
	for(int i=0;i<100;i++){
		vis[i]=false;
	}
	for(int i=0;i<100;i++){
		dist[i]=100;
	}
	/*for(auto x:dist){
		cout<<x<<endl;
	}*/
	dist[src]=0;
	priority_queue<node>q;
	q.push(node(src,0));
	int c=0;
	parent[src]=-1;
	while(q.empty()==false && c!=n){
		node top=q.top();
		q.pop();
		if(vis[top.v]==true){
			continue;
		}
		cout<<top.v<<":-\n";
		c++;
		dist[top.v]=top.dist;
		vis[top.v]=true;
		for(auto x:graph[top.v]){
			if(vis[x.first]==false){
				q.push(node(x.first,x.second+dist[top.v]));
		// Below given code is used when you have to print path...
				cout<<"x.first "<<x.first<<" x.second "<<x.second<<" top.v "<<top.v<<" dist[top.v] "<<dist[top.v]<<" dist[x.first] "<<dist[x.first]<<endl;
				if(x.second+dist[top.v]<dist[x.first]){
					dist[x.first]=x.second+dist[top.v];
					cout<<"Inside loop\n";
					cout<<top.v<<"\n";
					parent[x.first]=top.v;
					cout<<parent[x.first]<<"\n";
				}
			}
		}
	}
	cout<<endl;
	printf("Minimum distance from source %d is as follows:-\n",src);
	for(int i=1;i<=n;i++){
		cout<<i<<" "<<dist[i]<<"\n\n";
		//cout<<"immediate parent of "<<i<<" is "<<parent[i];
		cout<<"Full path is \n";
		Find_path(i);
		cout<<"\n\n";
	}	
	cout<<endl;
	return 0;
}


/*

void bfs(){
    memset(d,0x3f,sizeof(d)); //initilizing to a high value
    memset(inq,0,sizeof(inq));
    q.push(1); d[1] = 0; inq[1] = true;
    while (!q.empty()){
        int u = q.front();q.pop();
        inq[u] = false;
        int p = g[u].size();
        for (int i = 0; i < p; i++){
            int v = g[u][i].first, l = g[u][i].second;
            if (d[v] > d[u] + l){
                d[v] = d[u] + l;
                if (!inq[v]) q.push(v), inq[v] = true;
            }
        }
    }
}

*/




/*
#include <bits/stdc++.h>
#define INF 0x7fffffff
#define INFLL 1e17
#define PI 2*acos(0.0)
using namespace std;

#define FS first
#define SC second
#define PB(t) push_back(t)
#define ALL(t) t.begin(),t.end()
#define MP(x, y) make_pair((x), (y))
#define Fill(a,c) memset(&a, c, sizeof(a))

typedef pair<int, int> II;
typedef vector<int> VI;
typedef vector<II> VII;

vector<VII>G;

VI dijkstral( int source ){
    int u = source, v, d = 0, w;
    VI dist(G.size(), INF/2);
    priority_queue<II, VII, greater<II> >PQ;
    dist[ u ] = d;
    PQ.push( MP(dist[u], u) );
    while( !PQ.empty() ){
        u = PQ.top().second;
        d = PQ.top().first;
        PQ.pop();
        if( dist[u]<d )
            continue;
        dist[u] = d;
        for( int i=0; i < G[u].size(); i++){
            v = G[u][i].first;
            w = G[u][i].second;
            if( dist[v]>dist[u]+w){
            	dist[v] = dist[u]+w;
            	PQ.push( MP(dist[v],v) );
            }
        }
    }
    return dist;
}

*/
