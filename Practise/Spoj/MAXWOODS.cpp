#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int mat[205][205];
int dp[2][205][205]; // dp[1][x][y] :-right from x,y dp[0][x][y]:-left from x,y
string str;
int main(){
	int t,m,n;scanf("%d",&t);
	while(t--){
		scanf("%d%d",&m,&n);
		for(int k=0;k<2;k++){ 
			for(int i=0;i<205;i++){
				for(int j=0;j<205;j++){
					dp[k][i][j]=0;
				}
			}
		}
		for(int i=1;i<=m;i++){
			cin>>str;
			for(int j=0;j<n;j++){
				if(str[j]=='T'){
					mat[i][j+1]=2;
				}
				else if(str[j]=='0'){
					mat[i][j+1]=1;
				}
				else{
					mat[i][j+1]=0;
				}
			}
		}
		for(int i=m;i>=1;i--){
			for(int j=1;j<=n;j++){
				if(mat[i][j])
					dp[0][i][j]=max(dp[0][i][j-1],dp[1][i+1][j])+mat[i][j]-1;
			}
			for(int j=n;j>=1;j--){
				if(mat[i][j])
					dp[1][i][j]=max(dp[1][i][j+1],dp[0][i+1][j])+mat[i][j]-1;
			}
		}
		printf("%d\n",dp[1][1][1]);		
	}
	return 0;
}
