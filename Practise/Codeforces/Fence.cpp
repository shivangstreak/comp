#include<bits/stdc++.h>
using namespace std;
int dp[500005];
int h[500005];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%d",&h[i]);		
	}
	for(int i=0;i<m;i++){
		dp[0]+=h[0];
	}
	int sum=dp[0];
	int I=0;
	for(int i=1;i<=n-m;i++){
		dp[i]=dp[i-1]-h[i-1]+h[i+m-1];
		if(dp[i]<sum){
			sum=dp[i];
			I=i;
		}
	}
	cout<<I+1<<"\n";
	return 0;
}
