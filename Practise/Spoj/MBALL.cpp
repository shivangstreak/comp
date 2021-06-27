#include<bits/stdc++.h>  //Coin Change.....no of ways to get given sum ....
using namespace std;
#define ll long long
ll dp[100005];
int x[]={2,3,6,7,8};
int main(){
	int n,s;scanf("%d",&n);
	dp[0]=1;
	for(int j=0;j<5;j++){
		for(int i=x[j];i<100005;i++){
			if(dp[i-x[j]]!=0){
				dp[i]+=dp[i-x[j]];
			}
		}
	}
	
	while(n--){
		scanf("%d",&s);
		printf("%lld\n",dp[s]);
	}
	return 0;
}
