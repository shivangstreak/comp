#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
const int N=2*1e5+5;
ll BIT[N];
int A[N];
vector<int>g[N];
bool vis[N];
int c[N],discover_Time[N],end_Time[N];
int t=1;
void dfs(int i,int flag){
	c[i]=flag;
	discover_Time[i]=t;
	t++;
	vis[i]=true;
	for(auto x:g[i]){
		if(vis[x]==false){
			dfs(x,-flag);
		}
	}
	end_Time[i]=t-1;
}
ll giveSum(int indx){
	indx=discover_Time[indx];
	ll ans=0;
	while(indx>0){
		ans+=BIT[indx];
		indx-=indx&(-indx);
	}
	return ans;
}
void update(int indx,int val,int len){
	while(indx<=len){
		BIT[indx]+=val;
		indx+=indx&(-indx);
	}
}
void updateRange(int indx,int val,int len){
	val=c[indx]*val;
	update(discover_Time[indx],val,len);
	update(end_Time[indx]+1,-val,len);	
}
int main(){
	memset(vis,false,sizeof(vis));
	int x,l,r,n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
	}
	for(int i=1;i<=n-1;i++){
		scanf("%d%d",&l,&r);
		g[l].pb(r);
		g[r].pb(l);
	}
	dfs(1,1);
	/*for(int i=1;i<=n;i++){
		cout<<"c is "<<c[i]<<endl;
		cout<<"discover "<<i<<" "<<discover_Time[i]<<endl;
		cout<<"end_Time "<<i<<" "<<end_Time[i]<<endl;	
		cout<<endl;
	}*/
	while(m--){
		scanf("%d",&x);
		if(x==1){
			scanf("%d%d",&l,&r);
			updateRange(l,r,n);
		}
		else{
			scanf("%d",&l);
			cout<<A[l]+c[l]*giveSum(l)<<"\n";
		}		
	}
	return 0;
}
