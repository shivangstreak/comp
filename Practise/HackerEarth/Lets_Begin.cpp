#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+5;
ll dp[N];
int X[]={2,3,5,7};
int main(){
	int x,t;scanf("%d",&t);
	dp[1]=INT_MAX;
	dp[2]=1;
	dp[3]=1;
	dp[4]=2;
	dp[5]=1;
	dp[6]=2;
	dp[7]=1;
	for(int i=8;i<N;i++){
		dp[i]=INT_MAX;
		for(int j=0;j<4;j++){
			dp[i]=min(dp[i],dp[i-X[j]]+1);
		}
	}
	while(t--){
		scanf("%d",&x);
		if(dp[x]!=INT_MAX)
			printf("%lld\n",dp[x]);
		else{
			printf("-1\n");
		}		
	}

	return 0;
}	
