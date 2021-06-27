#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const ll INF=1e16;
struct node{
	ll t,a,w;
}arr[1005];
ll dp[1005][25][85];
int main(){
	int t,n,T,A,W;scanf("%d",&t);
	ll a,b,c;
	while(t--){
		scanf("%d%d%d",&T,&A,&n);
		for(int i=0;i<n;i++){
			scanf("%lld%lld%lld",&a,&b,&c);
			arr[i].t=a;
			arr[i].a=b;
			arr[i].w=c;			
		}
		for(ll i=0;i<=n;i++){
			for(ll t=0;t<=T;t++){
				for(ll a=0;a<=A;a++){
					if(t==0ll && a==0ll){
						dp[i][t][a]=0ll;
					}
					else if(i==0){ //All cylinder's counted
						dp[i][t][a]=INF;
					}
					else{
				dp[i][t][a]=dp[i-1][t][a];
				dp[i][t][a]=min(dp[i][t][a],dp[i-1][max(t-arr[i-1].t,0ll)][max(a-arr[i-1].a,0ll)]+arr[i-1].w);
					}
				}
			}
		}
		cout<<dp[n][T][A]<<"\n";
	}	
	return 0;
}
