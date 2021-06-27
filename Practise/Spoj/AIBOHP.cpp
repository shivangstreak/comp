#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
int dp[2][6105];
int Longest_common_subsequence(string str,int N){
	/*int result=-1; // for lonest common substring
	for(int i=1;i<=m;i++){
		for(int j=1;j<=m;j++){
			if(A[i-1]==A[m-j]){
				dp[i%2][j]=dp[(i-1)%2][j-1]+1;
				result=max(result,dp[i%2][j]);
			}
			else{
				dp[i%2][j]=0;
			}
		}
	}
	return result;*/
	for(int i=1;i<=N;i++){
		for(int j=1;j<=N;j++){
			if(str[i-1]==str[N-j]){
				dp[i%2][j]= 1+dp[(i-1)%2][j-1];
			}
			else{
				dp[i%2][j]=max(dp[(i-1)%2][j], dp[i%2][j-1]);
			}
		}
	}
	return dp[N%2][N];
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		memset(dp,0,sizeof(dp));
		string str;cin>>str;
		int N=str.size();
		printf("%d\n",N-Longest_common_subsequence(str,N));
	}
	return 0;
}
