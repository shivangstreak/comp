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
ll sol(int n,int T,int A){
	if(dp[n][T][A]!=-1){
		return dp[n][T][A];
	}
	else if(T==0 && A==0){
		dp[n][T][A]=0ll;
	}
	else if(n==0){
		dp[n][T][A]=INF;
	}
	else{
		dp[n][T][A]=min(sol(n-1,T,A),sol(n-1,max(T-arr[n-1].t,0ll),max(A-arr[n-1].a,0ll))+arr[n-1].w);
	}
	return dp[n][T][A];
}
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
		for(int i=0;i<1005;i++){
			for(int j=0;j<=25;j++){
				for(int k=0;k<85;k++){
					dp[i][j][k]=-1ll;
				}
			}
		}
		cout<<sol(n,T,A)<<"\n";
	}	
	return 0;
}
