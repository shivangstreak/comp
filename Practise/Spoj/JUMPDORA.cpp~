#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll dp[105][105],arr[105][105];
int main(){
	faster;
	int t;cin>>t;//scanf("%d",&t);
	while(t--){
		int m,n;
		string str;
		char ch;
		cin>>m>>n;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
					cin>>ch;
					if(ch=='#'){
						arr[i][j]=-1;
					}
					else{
						arr[i][j]=ch-'0';
					}
					dp[i][j]=INT_MAX;
			}
		}
		dp[0][0]=0;
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				if(arr[i][j]!=-1){
					if(i+1<m && arr[i+1][j]!=-1){
						dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
					}
					if(j+1<n && arr[i][j+1]!=-1){
						dp[i][j+1]=min(dp[i][j+1],dp[i][j]+1);
					}
					if(i+1+arr[i][j]<m && arr[i+1+arr[i][j]][j]!=-1){
						dp[i+1+arr[i][j]][j]=min(dp[i][j]+1,dp[i+1+arr[i][j]][j]);
					}
					if(j+1+arr[i][j]<n && arr[i][j+1+arr[i][j]]!=-1){
						dp[i][j+1+arr[i][j]]=min(dp[i][j]+1,dp[i][j+1+arr[i][j]]);
					}
				}
			}
		}
		if(dp[m-1][n-1]==INT_MAX){
			cout<<"-1\n";
		}
		else{
			cout<<dp[m-1][n-1]<<"\n";
		}
	}
	return 0;
}
