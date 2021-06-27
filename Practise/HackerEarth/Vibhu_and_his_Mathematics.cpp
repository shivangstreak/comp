#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD=1e9+7;
const int N=1e6+5;
ll dp[N];
int main(){
	int t,n;scanf("%d",&t);
	dp[0]=1;dp[1]=1;
	for(int i=2;i<N;i++){
		dp[i]=(dp[i-1]+(i-1)*dp[i-2])%MOD;
	}
	while(t--){
		scanf("%d",&n);
		printf("%lld\n",dp[n]);
	}
	return 0;
}
