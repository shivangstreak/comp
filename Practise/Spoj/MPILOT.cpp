#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e4+5;
ll dp[N][N];
ll captain[N],assis[N];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&captain[i],&assis[i]);
	}
	for(int l=1;l<n;l++){
		for(int j=0;j<n/2;j++){  // j represents how many captain needed...
			if(l==1 && j==0){
				dp[1][0]=assis[1];
				continue;
			}
			if((l-j)>n/2){
				dp[l][j]=INT_MAX;
				continue;
			}
			if(j==0){
				dp[l][j]=assis[l]+dp[l-1][j];
				continue;
			}
			if((l-j)<j){
				dp[l][j]=INT_MAX;
			}
			else{
				dp[l][j]=min(captain[l]+dp[l-1][j-1],assis[l]+dp[l-1][j]);
			}
		}
	}
	/*for(int l=1;l<=n;l++){
		for(int j=0;j<n/2;j++){
			cout<<dp[l][j]<<" ";
		}
		printf("\n");
	}*/
	printf("%lld\n",captain[n]+dp[n-1][(n/2)-1]);
	return 0;
}
