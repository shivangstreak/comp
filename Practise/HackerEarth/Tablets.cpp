#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
int arr[N],dp[N],dp1[N];
int main(){
	int n;scanf("%d",&n);
	fill(dp,dp+N,1);
	fill(dp1,dp1+N,1);
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	for(int i=1;i<n;i++){
		if(arr[i]>arr[i-1])
			dp[i]+=dp[i-1];
	}
	for(int i=n-2;i>=0;i--){
		if(arr[i]>arr[i+1])
			dp1[i]+=dp1[i+1];
	}
	int sum=0;
	for(int i=0;i<n;i++){
		//cout<<dp[i]<<" "<<dp1[i]<<endl;
		sum+=max(dp[i],dp1[i]);
	}
	printf("%d\n",sum);
	return 0;
}	
