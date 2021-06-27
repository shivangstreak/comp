#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int coin[105];
const int NN=105*505;
int dp[NN];
int call_dp(int m,int n){   // O(nm) time complexity and O(n) space complexity
	fill(dp,dp+NN,0);
	for(int i=0;i<m;i++){
		for(int w=n;w>=0;w--){
			if(coin[i]<=w){
				dp[w]=max(dp[w],dp[w-coin[i]]+coin[i]);
			}
		}
	}
	return dp[n];
}
int main(){
          int i,j,r,n,m,sum;
          scanf("%d", &n);
          for(i=0;i<n;i++)
          {
            scanf("%d",&m);
            sum=0;
            for(j=0;j<m;j++){
              scanf("%d", &coin[j]);
              sum+=coin[j];
            }
            r = call_dp(m, sum/2);
            r = sum - r*2;
            printf("%d\n", r);
          }
          return 0;
}	
