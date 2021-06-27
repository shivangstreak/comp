#include<bits/stdc++.h> //Getting TLE
using namespace std;
vector<int>g[100];
bool vis[100];
int parent[100];
int low[100],disc[100];
int Time,root,root_children;
map<pair<int,int>,int>mymap;
void chk_if_Biconnected(int u){
	low[u]=disc[u]=Time++;
	for(auto x:g[u]){
		if(disc[x]==-1){
			parent[x]=u;
			if(u==root)
				root_children++;
			chk_if_Biconnected(x);
			if(low[x]>disc[u]){
				mymap[{x,u}]=1;
				mymap[{u,x}]=1;
			}	
			low[u]=min(low[u],low[x]);
		}
		else if(x!=parent[u]){
			low[u]=min(low[u],disc[x]);
		}
	}
}
int main(){
	int a,b,c,n,m,k=0;
	while(true){
		k++;
		scanf("%d%d",&n,&m);
		if(n==0 && m==0){
			break;
		}
		int mn=INT_MAX;
		vector<int>v;
		vector<pair<int,int>>v1;
		for(int l=0;l<m;l++){
			scanf("%d%d%d",&a,&b,&c);
			v.push_back(c);
			v1.push_back({a,b});
		}
		vector<int>v_temp;
		int mask=0;
		while(mask<(1<<m)){
			v_temp.clear();
			int sum=0;
			for(int i=0;i<m;i++){
				if(mask & (1<<i)){
					v_temp.push_back(i); 
					sum+=v[i];
				}
			}
			mymap.clear();
			for(int i=0;i<100;i++){
				g[i].clear();
			}
			Time=0;
			memset(parent,-1,sizeof(parent));
			memset(disc,-1,sizeof(disc));
			for(auto x:v_temp){
				a=v1[x].first;
				b=v1[x].second;
				g[a].push_back(b);
				g[b].push_back(a);
			}
			chk_if_Biconnected(1);
			int flag=1;
			for(auto x:v1){
				if(mymap[x]==1){
					flag=0;
					break;	
				}
			}
			for(int i=1;i<=n;i++){
				if(disc[i]==-1){
					flag=0;
					break;
				}
			}
			if(flag==1){
				mn=min(mn,sum);
			}					
			mask++;
		}
		if(mn==INT_MAX){
			cout<<"There is no reliable net possible for test case "<<k<<".\n"; 
		}
		else{
			printf("The minimal cost for test case %d is %d.\n",k,mn);
		}
	}
	return 0;
}
