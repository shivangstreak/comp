#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+5;
ll dp[N],dp2[N];
int main(){
	int q,m,n,l,r,m1;scanf("%d",&n);
	scanf("%d",&m);
	m1=m;
	while(m--){
		scanf("%d%d",&l,&r);
		dp[l]+=1;
		dp[r+1]-=1;
	}
	for(int i=1;i<=n;i++){
		dp[i]+=dp[i-1];
	}
	for(int i=1;i<=n;i++){
		dp2[dp[i]]++;
	}
	for(int i=m1-1;i>=0;i--){
		dp2[i]+=dp2[i+1];
	}
	scanf("%d",&q);
	while(q--){
		scanf("%d",&m);
		printf("%lld\n",dp2[m]);
	}
	return 0;
}	
