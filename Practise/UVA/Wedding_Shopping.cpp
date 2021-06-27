#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int prices[25][25];
bool dp[25][205];
int main(){
        int t,m,n;scanf("%d",&t);
        while(t--){
                scanf("%d%d",&m,&n);
                for(int i=0;i<25;i++){
                        for(int j=0;j<205;j++){
                                dp[i][j]=false;
                        }
                }
                for(int i=0;i<n;i++){
                        scanf("%d",&prices[i][0]);
                        for(int j=1;j<=prices[i][0];j++){
                                scanf("%d",&prices[i][j]);
                        }
                }
                for(int i=0;i<=m;i++){
                        for(int j=1;j<=prices[0][0];j++){
                                if(i-prices[0][j]>=0){
                                       dp[0][m-prices[0][j]]=true;
                                }
                        }
                }
                for(int i=1;i<n;i++){
                        for(int j=0;j<=m;j++){
                                if(dp[i-1][j]==true){
                                        for(int k=1;k<=prices[i][0];k++){
                                                if(j-prices[i][k]>=0){
                                                        dp[i][j-prices[i][k]]=true;
                                                }
                                        }
                                }
                        }
                }
                int i;
                for(i=0;i<=m && dp[n-1][i]==false;i++);
                if(i==m+1){
                        printf("no solution\n");
                }
                else{
                        printf("%d\n",m-i);
                }
        }
	return 0;
}	
