#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
struct entry{
	ll r,h;
}arr[205];
ll dp[205];
bool cmp(const entry &A,const entry &B){
	return (A.r==B.r) ? A.h>B.h : A.r>B.r;
}
int main(){
	int n,t;scanf("%d",&t);
	ll R,H;
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%lld %lld",&R,&H);
			arr[i].r=R;
			arr[i].h=H;
		}
		sort(arr,arr+n,cmp);
		memset(dp,0,sizeof(dp));
		dp[0]=arr[0].h;
		for(int i=1;i<n;i++){
			for(int j=0;j<i;j++){
				if(arr[j].r>arr[i].r && arr[j].h>arr[i].h){
					dp[i]=max(dp[i],arr[i].h+dp[j]);
				}
				else if(dp[i]==0){
					dp[i]=arr[i].h;
				}
			}
		}
		ll mx=-1;
		for(int i=0;i<n;i++){
			mx=max(mx,dp[i]);
		}
		printf("%lld\n",mx);
	}
	return 0;
}	
