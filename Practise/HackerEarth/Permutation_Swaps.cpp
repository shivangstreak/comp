#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
vector<int>g[N];
bool vis[N];
int p[N],q[N];
vector<int>A,B;
void dfs(int i){
	vis[i]=true;
	A.pb(p[i]);
	B.pb(q[i]);
	int len=g[i].size();
	for(int k=0;k<len;k++){
		if(vis[g[i][k]]==false)
			dfs(g[i][k]);
	}
}
int main(){
	int a,b,t,n,m;scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<N;i++){
			g[i].clear();
			vis[i]=false;
		}
		for(int i=0;i<n;i++){
			scanf("%d",&p[i]);	
		}
		for(int i=0;i<n;i++){
			scanf("%d",&q[i]);
		}
		while(m--){
			scanf("%d %d",&a,&b);
			a--;b--;
			g[a].pb(b);
			g[b].pb(a);
		}
		int flag=0;
		for(int i=0;i<n;i++){
			A.clear();
			B.clear();
			if(vis[i]==false)
				dfs(i);
			sort(A.begin(),A.end());
			sort(B.begin(),B.end());
			int len=A.size();
			for(int hh=0;hh<len;hh++){
				if(A[hh]!=B[hh]){
					flag=1;
					break;
				}
			}
			if(flag==1)
				break;			
		}
		if(flag==1)
			printf("NO\n");
		else
			printf("YES\n");	
	}
	return 0;
}	
