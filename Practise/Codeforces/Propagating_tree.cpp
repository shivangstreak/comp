#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
const int N=200000+5;
int a[N],BIT[N];
vector<int>g[N];
bool vis[N];
int n;
int getSum(int indx,int ans){
	indx++;
	while(indx>0){
		ans+=BIT[indx];
		indx-=indx&(-indx);	
	}
	return ans;
}
void updatePoint(int indx,int val){
	indx++;
	while(indx<=n){
		BIT[indx]+=val;
		indx+=indx&(-indx);
	}
}
void dfs(int indx,int val){
	updatePoint(indx,val);
	//cout<<"indx is "<<indx<<" val "<<val<<endl;
	vis[indx]=true;
	for(auto x:g[indx]){
		if(vis[x]==false){
			dfs(x,-1*val);
		}
	}
}
int main(){
	int x,m,l,r;scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		updatePoint(i,a[i]);
	}
	for(int i=0;i<n-1;i++){
		scanf("%d%d",&l,&r);
		l--;r--;
		g[l].pb(r);
	}
	while(m--){
		scanf("%d",&x);
		if(x==1){
			memset(vis,false,sizeof(vis));
			scanf("%d%d",&l,&r);
			l--;
			//cout<<"l "<<l<<" r "<<r<<endl;
			dfs(l,r);
			/*for(int i=0;i<n;i++){
				printf("%d\n",getSum(i,0)-getSum(i-1,0));
			}*/
		}
		else{
			scanf("%d",&l);
			l--;
			printf("%d\n",getSum(l,0)-getSum(l-1,0));
		}
	}
	return 0;
}
