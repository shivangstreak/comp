#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int d[105];
//ll dp[10005][10005];
map<pair<int,int>,int>dp;
int t,p,q;
ll solve(int a,int b){
  if(dp.find({a,b})!=dp.end()){
    return dp[{a,b}];
  }
  int temp=0,r=0;
  for(int i=0;i<q;i++){
      if(d[i]>=a && d[i]<=b){
          temp=(b-a)+solve(a,d[i]-1)+solve(d[i]+1,b);
          if(r==0 || temp<r){
            r=temp;
          }
      }
  }
  dp[{a,b}]=r;
  return dp[{a,b}];
}
int main(){
        scanf("%d",&t);
        for(int k=1;k<=t;k++){
              dp.clear();
               /*for(int i=0;i<105;i++){
                 for(int j=0;j<105;j++){
                   dp[i][j]=-1;
                 }
               }*/
               scanf("%d%d",&p,&q);
               for(int i=0;i<q;i++){
                        scanf("%d",&d[i]);
               }
               printf("Case #%d: %d\n",k,solve(1,p));
        }
	return 0;
}

