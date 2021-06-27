#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a[100005];
bool vis[100005];
vector<int>g[100005];
int n,m,res=0;
void dfs(int i,int b,int parent,int ccc){
	vis[i]=true;
	if(parent!=-1 && ccc!=1){
		//int val=a[parent];
		if(a[i]==1){
			b++;
		}
		else{
			b=0;
		}
		if(b>m){
			ccc=1;
		}
		/*else if(val==0){
			b=0;
		}*/
	}
		int flag=1;
		for(auto x:g[i]){
			if(vis[x]==false){
				flag=0;
				dfs(x,b,i,ccc);
			}
		}
		if(flag==1 && ccc!=1){
			res++;
		}
}
int main(){
	int A,B;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=0;i<n-1;i++){
		scanf("%d%d",&A,&B);
		g[A].push_back(B);
		g[B].push_back(A);
	}
	if(a[1]==1)
		dfs(1,1,-1,0);
	else{
		dfs(1,0,-1,0);
	}
	cout<<res<<"\n";
	return 0;
}
