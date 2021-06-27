#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int MN=-1*1e9;
int profit[105][105];
int dp[1005][105];
bool endCity[105];
int c,s,e,t,d;
void init(){
      memset(endCity,false,sizeof(endCity));
      for(int i=0;i<1005;i++){
        for(int j=0;j<105;j++){
                if(i<105){
                        profit[i][j]=0;
                }
                dp[i][j]=-1;
        }
      }
}
int rec(int days,int city){
        if(days>t || city>c){
                return MN;
        }
        if(dp[days][city]!=-1){
                return dp[days][city];
        }
        if(days==t){
                if(endCity[city]==true){
                       dp[days][city]=0;
                       return dp[days][city];
                }
                else{
                        return MN;
                }
        }
        dp[days][city]=0;
        for(int i=1;i<=c;i++){
                if(i!=city){
                        dp[days][city]=max(dp[days][city],profit[city][i]+rec(days+1,i));
                }
        }
        return dp[days][city];
}
int main(){
        while(true){
                scanf("%d%d%d%d",&c,&s,&e,&t);
                if(c==0 && s==0 && e==0 && t==0){
                        break;
                }
                init();
                for(int i=1;i<=c;i++){
                        for(int j=1;j<=c;j++){
                                scanf("%d",&profit[i][j]);
                        }
                }
                for(int i=0;i<e;i++){
                        scanf("%d",&d);
                        endCity[d]=true;
                }
                printf("%d\n",rec(0,s));
        }
	return 0;
}
