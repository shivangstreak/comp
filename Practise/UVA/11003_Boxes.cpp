#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int w[1005],c[1005];
int dp[1005][6005];
int n;
int fxn(int indx,int bal){
        if(indx==n){
                return 0;
        }
        if(dp[indx][bal]!=-1){
                return dp[indx][bal];
        }
        if(w[indx]<=bal){
                return dp[indx][bal]=max(fxn(indx+1,bal),1+fxn(indx+1,min(bal-w[indx],c[indx])));
        }
        else{
                return dp[indx][bal]=fxn(indx+1,bal);        
        }
}
int main(){
        while(true){
                scanf("%d",&n);
                if(n==0){
                        break;
                }
                for(int i=0;i<1005;i++){
                        for(int j=0;j<6005;j++){
                                dp[i][j]=-1;
                        }
                }
                for(int i=0;i<n;i++){
                        scanf("%d%d",&w[i],&c[i]);
                }
                printf("%d\n",fxn(0,6003));
        }
	return 0;
}	


