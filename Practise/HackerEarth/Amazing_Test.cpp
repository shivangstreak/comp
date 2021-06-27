#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[105];
const int SUM=1e5+5;
int dp[105][SUM];
int t,n,x,sum;
void callDP(){
        for(int i=0;i<=n;i++){
               for(int j=0;j<=x;j++){
                        if(i==0 || j==0){
                               dp[i][j]=0;     
                        }
                        else if(arr[i-1]<=j){
                                dp[i][j]=max(dp[i-1][j-arr[i-1]]+arr[i-1],dp[i-1][j]);
                        }
                        else{
                                dp[i][j]=dp[i-1][j];
                        }
               } 
        }
}
int main(){
        scanf("%d",&t);
        while(t--){
                sum=0;
                scanf("%d%d",&n,&x);
                for(int i=0;i<n;i++){
                        scanf("%d",&arr[i]);
                        sum+=arr[i];
                }
                if(sum<=x){
                        printf("YES\n");
                        continue;
                }
                callDP();
                if(sum-dp[n][x]<=x){
                        printf("YES\n");
                }
                else{
                        printf("NO\n");
                }
        }
	return 0;
}	
