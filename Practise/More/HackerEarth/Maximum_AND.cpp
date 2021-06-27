#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll a,b;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		scanf("%lld%lld",&a,&b);
		ll ans;
		if(b-a<2){
			ans=(a&b);
		}	
		else if(b&1){
			ans=(b-1)&b;
		}
		else{
			ans=(b-1)&(b-2);
		}
		printf("%lld\n",ans);
	}
	return 0;
}	
