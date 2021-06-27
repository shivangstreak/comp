#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
const int MOD=1e9+7;
ll BITS0[N],BITS1[N],BITSL[N],A[N];
void update(ll *BITS,int indx,int val){
	while(indx<=N){
		BITS[indx]=(BITS[indx]+(val%MOD))%MOD;
		indx+=indx&(-indx);
	}
}
ll giveSum(ll *BITS,int indx){
	ll ans=0;
	while(indx>0){
		ans=(ans+BITS[indx])%MOD;
		indx-=indx&(-indx);
	}
	return ans;
}
int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%lld",&A[i]);
	}
	ll A_is_small,A_is_large;
	ll ans=0;
	for(int i=0;i<n;i++){
		A_is_small=((giveSum(BITS1,N)-giveSum(BITS1,A[i]))%MOD+(giveSum(BITSL,N)-giveSum(BITSL,A[i])%MOD))%MOD;
		if(A_is_small<0){
			A_is_small+=MOD;
		}
		A_is_large=(giveSum(BITS0,A[i]-1)%MOD+giveSum(BITSL,A[i]-1)%MOD)%MOD;
		ans=(ans+A_is_small+A_is_large)%MOD;
		update(BITSL,A[i],1);
		update(BITS0,A[i],A_is_small);
		update(BITS1,A[i],A_is_large);
	}
	printf("%lld\n",ans);
	return 0;
}
