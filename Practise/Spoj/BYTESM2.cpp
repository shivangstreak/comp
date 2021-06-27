#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[105][105];
int dp[105][105];
int main(){
        int h,w,t;scanf("%d",&t);
        while(t--){
                scanf("%d%d",&h,&w);
                for(int i=0;i<h;i++){
                        for(int j=0;j<w;j++){
                                scanf("%d",&arr[i][j]);
                        }
                }
                for(int j=0;j<w;j++){
                        dp[h-1][j]=arr[h-1][j];
                }
                for(int i=h-2;i>=0;i--){
                        for(int j=0;j<w;j++){
                                if(j==0){
                                        dp[i][j]=arr[i][j]+max(dp[i+1][j],dp[i+1][j+1]);
                                }
                                else if(j==w-1){
                                        dp[i][j]=arr[i][j]+max(dp[i+1][j],dp[i+1][j-1]);
                                }
                                else{
                                        dp[i][j]=arr[i][j]+max(max(dp[i+1][j],dp[i+1][j-1]),dp[i+1][j+1]);
                                }
                        }
                }
                int mx=INT_MIN;
                for(int j=0;j<w;j++){
                        mx=max(mx,dp[0][j]);
                }
                printf("%d\n",mx);
        }
	return 0;
}	
