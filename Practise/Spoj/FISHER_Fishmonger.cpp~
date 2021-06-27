#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
#define INF INT_MAX
pair<ll,ll> dp[55][1005];
ll n,t;
ll tolls[55][55];
ll Time[55][55];
void init(){
        for(int i=0;i<55;i++){
                for(int j=0;j<1005;j++){
                        dp[i][j].first=-1;
                        dp[i][j].second=-1;
                }
        }
}
pair<ll,ll> fxn(int id,int time_left){
        if(time_left<0){
                return {INF,INF};
        }
        if(id==n-1){
                return {0,0}; // No need to pay more tools and reached destination within time 
        }
        if(dp[id][time_left].first!=-1){
                return dp[id][time_left];
        }
        pair<ll,ll>ans=make_pair(INF,INF);
        for(int j=0;j<n;j++){
           if(j!=id){
                pair<ll,ll> Next=fxn(j,time_left-Time[id][j]);
                if(Next.first+tolls[id][j]<ans.first){
                   ans.first=Next.first+tolls[id][j];
                   ans.second=Next.second+Time[id][j];        
                }
            }
        }
        dp[id][time_left]=ans;
        return dp[id][time_left];
}
int main(){
        while(true){
                init();
                scanf("%lld%lld",&n,&t);
                if(n==0 && t==0){
                        break;
                }
                for(int i=0;i<n;i++){
                        for(int j=0;j<n;j++){
                                scanf("%lld",&Time[i][j]);
                        }
                }
                for(int i=0;i<n;i++){
                        for(int j=0;j<n;j++){
                                scanf("%lld",&tolls[i][j]);
                        }
                }                
                pair<ll,ll> ans=fxn(0,t);
                printf("%lld %lld\n",ans.first,ans.second);
        }
	return 0;
}	
