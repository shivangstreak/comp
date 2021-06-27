#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
double P[1005],dist[1005];
double dp[1005];
int main(){
        memset(dp,0,sizeof(dp));
        int n,L,D;
        scanf("%d%d%d",&n,&L,&D);
        for(int i=1;i<=n;i++){
                scanf("%lf",&P[i]);
        }
        for(int j=1;j<=n;j++){
                scanf("%lf",&dist[j]);
        }
        P[0]=1.0;
        dist[0]=0;
        dist[n+1]=D;
        dp[n+1]=1.0;
        bool imp=false;
        for(int i=n;i>=0;i--){
                bool flag=false;
                for(int j=i+1;j<=n+1;j++){
                        if(dist[j]-dist[i]<=L){
                                dp[i]=max(dp[i],P[i]*dp[j]);
                                flag=true;
                        }
                        else{
                                break;
                        }
                }
                if(flag==false){
                        printf("IMPOSSIBLE\n");
                        imp=true;
                        break;
                }
        }
        if(!imp){
                printf("%lf\n",dp[0]);
        }
	return 0;
}	


