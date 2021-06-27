#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[10005];
int main(){
        int m,n,t;
        while(scanf("%d%d%d",&m,&n,&t)!=EOF){
                int mn=min(m,n);
                int mx=max(m,n);
                memset(dp,0,sizeof(dp));
                dp[mn]=1;
                dp[mx]=1;
                for(int i=mn;i<=t;i++){
                        if(dp[i]!=0){
                                if(i+mn<=t){
                                        dp[i+mn]=max(dp[i]+1,dp[i+mn]);
                                }
                                if(i+mx<=t){
                                        dp[i+mx]=max(dp[i]+1,dp[i+mx]);
                                }                        
                        }
                }
                if(dp[t]!=0){
                        printf("%d\n",dp[t]);
                }
                else{
                        int flag=0;
                        for(int i=t-1;i>=0;i--){
                                if(dp[i]>0){
                                        printf("%d %d\n",dp[i],t-i);
                                        flag=1;
                                        break;
                                }
                        }
                        if(flag==0){
                                printf("0 %d\n",t);
                        }
                }
        }
	return 0;
}	
