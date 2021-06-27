#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll unsigned long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll a,b,c,d,k;
ll fxn(ll t){
	return a*t*t*t+b*t*t+c*t+d; 
}
ll Binary_Search(ll start,ll end){
	ll mid;
	ll rightmost=end;
	while(start<=end){
		mid=(start+end)>>1;
		ll t=fxn(mid);
		if(t<=k && (mid==rightmost || fxn(mid+1)>k)){
			return mid;
		}
		if(t>k){
			end=mid-1;
		}
		else if(t<k){ // t<=k
			start=mid+1;
		}
	}
}
int main(){
	int T;scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld%lld%lld",&a,&b,&c,&d,&k);
		ll d=1e6+6;
		printf("%llu\n",Binary_Search(0,d));
	}
	return 0;
}
