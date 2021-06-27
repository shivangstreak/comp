#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
const int MOD=1e9+7;
char str[N];
ll dp[N];
int last[N];
int main(){
	int len,t;scanf("%d",&t);
	while(t--){
		memset(dp,0,sizeof(dp));
		memset(last,0,sizeof(last));
		scanf("%s",str);
		len=strlen(str);
		dp[0]=1;
		// dp[i] represent all distinct subsequence in str[1...i]
		for(int i=1;i<=len;i++){
			dp[i]=(dp[i-1]*2)%MOD;
			if(last[str[i-1]]!=0){
				dp[i]=dp[i]-dp[last[str[i-1]]-1];
				dp[i]=(MOD+dp[i]%MOD)%MOD;
			}
			last[str[i-1]]=i;
		}
		printf("%lld\n",dp[len]);
	}
	return 0;
}
