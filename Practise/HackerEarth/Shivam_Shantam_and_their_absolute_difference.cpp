#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int MOD=1e9+7;
int n,q;
ll dp[205][400005][2];
int A[205],B[205];
ll fxn(int indx,int diff,int flag){
        if(dp[indx][diff][flag]!=-1){
                return dp[indx][diff][flag];
        }
        if(indx==n){
                return (diff<=q);
        }
        if(flag==1){
                diff=-diff;
        }
        ll ans=0,actual_diff;

        actual_diff=diff+A[indx]-B[indx];
        ans+=fxn(indx+1,abs(actual_diff),actual_diff<0)%MOD;

        actual_diff=diff+A[indx];
        ans+=fxn(indx+1,abs(actual_diff),actual_diff<0)%MOD;

        actual_diff=diff-B[indx];
        ans+=fxn(indx+1,abs(actual_diff),actual_diff<0)%MOD;

        actual_diff=diff;
        ans+=fxn(indx+1,abs(actual_diff),actual_diff<0)%MOD;

        dp[indx][diff][flag]=ans;

        return ans;
}
int main(){
        for(int i=0;i<205;i++){
                for(int j=0;j<400005;j++){
                        for(int k=0;k<2;k++){
                                dp[i][j][k]=-1;
                        }
                }
        }
        scanf("%d",&n);
        for(int i=0;i<n;i++){
                scanf("%d",&A[i]);
        }
        for(int j=0;j<n;j++){
                scanf("%d",&B[j]);
        }
        scanf("%d",&q);
	printf("%lld\n",fxn(0,0,0));
	return 0;
}
