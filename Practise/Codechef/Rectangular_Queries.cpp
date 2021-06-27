#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int mat[305][305];
int dp[12][305][305];
int r1,r2,c1,c2,q,n;
int main(){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                        scanf("%d",&mat[i][j]);
                }
        }
        for(int k=1;k<=10;k++){
                for(int i=0;i<n;i++){
                        for(int j=0;j<n;j++){
                                dp[k][i][j]=(mat[i][j]==k);
                                if(i>0){
                                        dp[k][i][j]+=dp[k][i-1][j];
                                }
                                if(j>0){
                                        dp[k][i][j]+=dp[k][i][j-1];
                                }
                                if(i>0 && j>0){
                                        dp[k][i][j]-=dp[k][i-1][j-1];
                                }
                        }
                }
        }
        scanf("%d",&q);
        while(q--){
                scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
                r1--;
                r2--;
                c1--;
                c2--;
                int cnt=0;
                for(int k=1;k<=10;k++){
                        int sum=dp[k][r2][c2];
                        if(r1>0){
                                sum-=dp[k][r1-1][c2];
                        }
                        if(c1>0){
                                sum-=dp[k][r2][c1-1];
                        }
                        if(r1>0 && c1>0){
                                sum+=dp[k][r1-1][c1-1];
                        }
                        if(sum>0){
                                cnt++;
                        }
                }
                printf("%d\n",cnt);
        }
	return 0;
}	
