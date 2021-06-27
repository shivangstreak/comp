#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[15][1005];
int Cost[15][15][1005];
#define INF 99999999
void init(){
        for(int i=0;i<15;i++){
                for(int j=0;j<1005;j++){
                        dp[i][j]=INF;
                }
        }
}
int main(){
        int Case=1;
        while(true){
                int n,days,d;
                scanf("%d%d",&n,&days);
                if(n==0 && days==0){
                        break;
                }
                init();
                for(int i=1;i<=n;i++){
                        for(int j=1;j<=n;j++){
                                if(i!=j){
                                        scanf("%d",&d);
                                        Cost[i][j][0]=d;
                                        for(int k=1;k<=d;k++){
                                                scanf("%d",&Cost[i][j][k]);
                                        }
                                }
                        }
                }
                dp[1][0]=0;
                for(int j=1;j<=days;j++){
                        for(int i=1;i<=n;i++){
                                for(int k=1;k<=n;k++){
                                        if(i!=k){
                                                int Cost_k_i=Cost[k][i][((j-1)%Cost[k][i][0])+1];
                                                if(Cost_k_i!=0 && dp[k][j-1]!=INF)
                                                        dp[i][j]=min(dp[k][j-1]+Cost_k_i,dp[i][j]);
                                        }
                                }
                        }
                }
                printf("Scenario #%d\n",Case++);
                if(dp[n][days]!=INF){
                        printf("The best flight costs %d.\n",dp[n][days]);
                }
                else{
                        printf("No flight possible.\n");
                }
                printf("\n");
        }
	return 0;
}	
