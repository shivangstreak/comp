#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
const int N=1e5+6;
vector<int>g[N];
int dist[N];
int d,n,s,t;
int flag;
int c=0;
void bfs(){
	queue<int>q;
	q.push(s);
	dist[s]=0;
	while(q.empty()==false){
		int top=q.front();
		q.pop();
		if(top==t){
			flag=1;
			break;
		}
		for(auto x:g[top]){
			if(dist[x]==-1){
				dist[x]=dist[top]+1;
				q.push(x);			
			}			
		}
	}
}
int main(){
	memset(dist,-1,sizeof(dist));
	scanf("%d%d%d",&n,&s,&t);
	for(int i=0;i<n;i++){
		scanf("%d",&d);
		g[i+1].pb(d);
	}
	bfs();
	if(flag==0){
		printf("-1\n");
	}
	else{
		printf("%d\n",dist[t]);		
	}
	return 0;
}
