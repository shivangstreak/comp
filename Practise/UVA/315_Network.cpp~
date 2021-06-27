#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
vector<int>g[105];
bool vis[105];
bool art[105];
int parent[105];
int disc[105],low[105];
int d,root,c;
char str[1005];
int Time;
void f(){
	int size=strlen(str);
	int temp=0;
	for(int i=0;i<size;i++){
		if(str[i]==' '){
			if(temp!=0)
			g[d].pb(temp);
			g[temp].pb(d);
			temp=0;
		}
		else{
			temp=temp*10+(str[i]-'0');
		}
	}
	if(temp!=0){
		g[d].pb(temp);;
		g[temp].pb(d);
	}
}
void articulation_points(int u){
	vis[u]=true;
	Time++;
	disc[u]=Time;
	low[u]=Time;
	int children=0;
	int size=g[u].size();
	for(int j=0;j<size;j++){
		int v=g[u][j];
		if(vis[v]==false){
			parent[v]=u;
			children++;
			articulation_points(v);
			if(parent[u]==-1 && children>1){
				art[u]=true;
			}
			if(parent[u]!=-1 && low[v]>=disc[u]){
				art[u]=true;
			}
			low[u]=min(low[u],low[v]);
		}
		else if(v!=parent[u]){
			low[u]=min(low[u],disc[v]);
		}
	}
}
int main(){
	int n;
	while(true){
		c=0;
		Time=0;
		for(int i=0;i<105;i++){
			g[i].clear();
			vis[i]=false;
			art[i]=false;
			disc[i]=0;
			low[i]=0;
			parent[i]=-1;
		}
		scanf("%d",&n);
		if(n==0)
			break;
		scanf("%d",&d);
		while(d!=0){
			//cout<<d<<endl;
			scanf("%[^\n]%*c",str);
			f();
			/*cout<<d<<endl;
			for(auto x:g[d]){
				cout<<x<<" ";
			}
			cout<<endl;*/
			scanf("%d",&d);		
		}
		for(int i=1;i<=n;i++){
			if(vis[i]==false){
				articulation_points(i);
			}
		}
		for(int i=1;i<=n;i++){
			if(art[i]==true)
				c++;
		}
		printf("%d\n",c);
	}
	return 0;
}
