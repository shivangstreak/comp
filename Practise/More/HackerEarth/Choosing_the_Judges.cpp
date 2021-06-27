#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e4+5;
ll X[N],dp[N];
int main(){
	int T,n;scanf("%d",&T);
	for(int t=1;t<=T;t++){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lld",&X[i]);
		dp[1]=X[1];
		dp[2]=max(dp[1],X[2]);
		for(int i=3;i<=n;i++){
			dp[i]=max(X[i]+dp[i-2],dp[i-1]);
		}
		printf("Case %d: %lld\n",t,dp[n]);
	}
	return 0;
}	
