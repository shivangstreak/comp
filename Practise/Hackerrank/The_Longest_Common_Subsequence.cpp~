#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int a[105],b[105];
int n,m;
int dp[105][105];
vector<int>res;
void LCS(){
        for(int i=0;i<=n;i++){
                for(int j=0;j<=m;j++){
                        if(i==0 || j==0){
                                dp[i][j]=0;
                        }
                        else if(a[i-1]==b[j-1]){
                                dp[i][j]=dp[i-1][j-1]+1;
                        }
                        else{
                                dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
                        }
                }
        }
}
void build_LCS(){
        int i,j;
        i=n;j=m;
        while(i>0 && j>0){
                if(a[i-1]==b[j-1]){
                        res.pb(a[i-1]);
                        i--;
                        j--;
                }
                else if(dp[i-1][j]>dp[i][j-1]){
                        i--;
                }
                else{
                        j--;
                }
        }
        for(int i=dp[n][m]-1;i>=0;i--){
                printf("%d ",res[i]);
        }
        printf("\n");
}
int main(){
        res.clear();
        cin>>n>>m;
        for(int i=0;i<n;i++){
                cin>>a[i];
        }
        for(int j=0;j<m;j++){
                cin>>b[j];
        }
        LCS();
        build_LCS();
	return 0;
}	


