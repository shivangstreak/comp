#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int arr[55];
int dp[55][55];
int f(int start,int end){
	if(end-start==1){
		return 0;
	}
	if(dp[start][end]!=-1){
		return dp[start][end];
	}
	int mn=INT_MAX;
	for(int i=start+1;i<end;i++){
		mn=min(mn,f(start,i)+f(i,end)+(arr[end]-arr[start]));
	}
	dp[start][end]=mn;
	return mn;
}
int main(){
	int l,n;
	while(true){
		scanf("%d",&l);
		if(l==0){
			break;
		}
		scanf("%d",&n);
		arr[0]=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&arr[i]);
		}
		arr[n+1]=l;
		sort(arr,arr+n+1);
		memset(dp,-1,sizeof(dp));
		printf("The minimum cutting is %d.\n",f(0,n+1));
	}
	return 0;
}
