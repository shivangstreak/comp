#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll dp[2][400005][2];
int A[205],B[205];
const ll MOD=1e9+7;
int main(){
        int n,q;scanf("%d",&n);
        for(int i=1;i<=n;i++){
                scanf("%d",&A[i]);
        }
        for(int j=1;j<=n;j++){
                scanf("%d",&B[j]);
        }      
        scanf("%d",&q);
        dp[0][0][0]=1;
        for(int i=1;i<=n;i++){
                // Initialize!!!
                for(int j=0;j<400005;j++){
                        for(int k=0;k<2;k++){
                                dp[i%2][j][k]=0;
                        }        
                }
                
                for(int j=0;j<400005;j++){
                        for(int k=0;k<2;k++){
                                if(j==0 && k==1)
                                        continue;
                                if(dp[(i-1)%2][j][k]==0){
                                        continue;
                                }
                                int actual_diff=j,new_diff;
                                if(k==1){
                                        actual_diff=-j;
                                }
                                
                                new_diff=actual_diff+A[i]-B[i];
                                dp[i%2][abs(new_diff)][(new_diff<0)]+=dp[(i-1)%2][j][k];
                                if(dp[i%2][abs(new_diff)][(new_diff<0)]>=MOD){
                                        dp[i%2][abs(new_diff)][(new_diff<0)]%=MOD;
                                }       

                                new_diff=actual_diff+A[i];
                                dp[i%2][abs(new_diff)][(new_diff<0)]+=dp[(i-1)%2][j][k];
                                if(dp[i%2][abs(new_diff)][(new_diff<0)]>=MOD){
                                        dp[i%2][abs(new_diff)][(new_diff<0)]%=MOD;
                                }           

                                new_diff=actual_diff-B[i];
                                dp[i%2][abs(new_diff)][(new_diff<0)]+=dp[(i-1)%2][j][k];
                                if(dp[i%2][abs(new_diff)][(new_diff<0)]>=MOD){
                                        dp[i%2][abs(new_diff)][(new_diff<0)]%=MOD;
                                }          

                                new_diff=actual_diff;
                                dp[i%2][abs(new_diff)][(new_diff<0)]+=dp[(i-1)%2][j][k];
                                if(dp[i%2][abs(new_diff)][(new_diff<0)]>=MOD){
                                        dp[i%2][abs(new_diff)][(new_diff<0)]%=MOD;
                                }         

                        }
                }
        }
                ll ans=0;
                for(int i=0;i<=q;i++){
                        for(int k=0;k<2;k++){
                                ans+=dp[n%2][i][k];
                                if(ans>=MOD)
                                      ans%=MOD;
                        }        
                }    
               printf("%lld\n",ans);     
	return 0;
}	
