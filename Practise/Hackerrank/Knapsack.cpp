#include<bits/stdc++.h>
using namespace std;
int dp[2005];
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,k;scanf("%d%d",&n,&k);
		memset(dp,0,sizeof(dp));
		vector<int>v;
		for(int i=0;i<n;i++){
			int d;scanf("%d",&d);
			v.push_back(d);
		}
		sort(v.begin(),v.end());
		for(int i=1;i<=k;i++){
			for(int j=0;j<n;j++){
				if(i>=v[j])
					dp[i]=max(dp[i],v[j]+dp[i-v[j]]);
			}
		}
		cout<<dp[k]<<"\n";
	}
	return 0;
}
