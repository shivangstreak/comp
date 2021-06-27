#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N];
int dp[N];
int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=0;i<n;i++){
		int mx=0;
		for(int j=2;j*j<=a[i];j++){
			if(a[i]%j==0){
				mx=max(mx,max(dp[a[i]/j],dp[j]));
			}
		}
		dp[a[i]]=mx+1;
		for(int j=2;j*j<=a[i];j++){
			if(a[i]%j==0){
				dp[j]=dp[a[i]];
				dp[a[i]/j]=dp[a[i]];
			}
		}		
	}
	int mx=INT_MIN;
	for(int i=0;i<n;i++){
		mx=max(mx,dp[a[i]]);
	}
	cout<<mx<<"\n";
	return 0;
}
