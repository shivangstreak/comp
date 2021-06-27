#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[505][(1<<10)+10];
char str[505][15]; 
int t,n,k;
void init(){
        for(int i=0;i<505;i++){
                for(int j=0;j<(1<<10)+10;j++){
                        dp[i][j]=-1;                        
                }
        }
}
int fxn(int indx,int mask){
        if(indx==n){
                return 0;
        }        
        if(dp[indx][mask]!=-1){
                return dp[indx][mask];
        }
        int ans=1e9;
        for(int i=0;i<k;i++){
                if(str[indx][i]=='0'){
                        continue;
                }
                if(mask &(1<<i)){
                        ans=min(ans,fxn(indx+1,mask));
                }
                else{
                        ans=min(ans,1+fxn(indx+1,mask | (1<<i)));
                }
        }
        dp[indx][mask]=ans;
        return dp[indx][mask];
}
int main(){
        scanf("%d",&t);
        while(t--){
                init();
                scanf("%d%d",&n,&k);
                for(int i=0;i<n;i++){
                        scanf("%s",str[i]);
                }
                printf("%d\n",fxn(0,0));
        }        
	return 0;
}	


