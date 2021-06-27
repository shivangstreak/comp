#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
#define ll long long 
int l[N],b[N],stood;
int dp[2][N];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d",&b[i],&l[i]);
	}
	dp[0][1]=b[1];
	dp[1][1]=l[1];
	for(int j=2;j<=n;j++){
		for(int i=0;i<2;i++){
			if(i==0){
				dp[i][j]=max(dp[0][j-1]+abs(l[j]-l[j-1])+b[j],dp[1][j-1]+abs(l[j]-b[j-1])+b[j]);
			}
			else{
				dp[i][j]=max(dp[0][j-1]+abs(b[j]-l[j-1])+l[j],dp[1][j-1]+abs(b[j]-b[j-1])+l[j]);
			}				
		}
	}
	printf("%d\n",max(dp[0][n],dp[1][n]));
	return 0;
}
