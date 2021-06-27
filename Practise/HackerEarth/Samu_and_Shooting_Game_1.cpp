#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e3+4;
double dp[N][N];
int n,x,y,w,p1,p2;
double P1,P2;
int main(){
        int t;scanf("%d",&t);
        while(t--){
                scanf("%d%d%d%d%d%d",&x,&y,&n,&w,&p1,&p2);
                P1=p1*0.01;
                P2=p2*0.01;
                for(int i=0;i<=n;i++){
                        dp[i][0]=1;
                }
                for(int j=1;j<=w;j++){
                        dp[0][j]=0;
                }
                for(int i=1;i<=n;i++){
                        for(int j=1;j<=w;j++){
                                dp[i][j]=max(P1*dp[i-1][max(j-x,0)]+(1-P1)*dp[i-1][max(j,0)],P2*dp[i-1][max(j-y,0)]+(1-P2)*dp[i-1][max(j,0)]);
                        }
                }
                printf("%.6lf\n",dp[n][w]*100);
        }
	return 0;
}	


