#include<bits/stdc++.h>
using namespace std;
char A[2005],B[2005];
int k;
int dp[2005][2005];
int main(){
	scanf("%s%s",A,B);
	scanf("%d",&k);
	int lena=strlen(A);
	int lenb=strlen(B);
	for(int i=0;i<=lena;i++){
		dp[i][0]=k*i;
	}
	for(int i=0;i<=lenb;i++){
		dp[0][i]=k*i;
	}
	for(int i=1;i<=lena;i++){
		for(int j=1;j<=lenb;j++){
			dp[i][j]=min(min(dp[i-1][j],dp[i][j-1])+k,dp[i-1][j-1]+abs(A[i-1]-B[j-1]));
		}
	}
	printf("%d\n",dp[lena][lenb]);
	return 0;
}
