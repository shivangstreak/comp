#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int dp[35][35];
int fxn(int f,int h){
        if(f==0 && h!=0){
                return 1;
        }
        else if(dp[f][h]!=-1){
                return dp[f][h];
        }
        else if(f>0 && h==0){
                dp[f][h] = fxn(f-1,1);
        }
        else{
                dp[f][h]= fxn(f-1,h+1)+fxn(f,h-1);
        }
        return dp[f][h];
}
int main(){
        int t;scanf("%d",&t);
        while(t--){
                for(int i=0;i<35;i++){
                        for(int j=0;j<35;j++){
                                dp[i][j]=-1;
                        }
                }
                int n;
                scanf("%d",&n);
                printf("%d\n",fxn(n,0));
        }       
	return 0;
}	


