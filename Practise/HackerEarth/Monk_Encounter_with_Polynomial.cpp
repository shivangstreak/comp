#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int a,b,c;
ll k;
ll fxn(ll x){
	return (a*x*x+b*x+c);
}
int main(){
	ll start,end,mid,pos;
	int t;scanf("%d",&t);
	while(t--){
		scanf("%d%d%d%lld",&a,&b,&c,&k);
		start=0,end=100006;
		pos=2*1e9;
		while(start<=end){
			mid=(start+end)>>1;
			if(fxn(mid)>=k){
				pos=min(pos,mid);
				end=mid-1;
			}
			else{
				start=mid+1;
			}
		}
		printf("%lld\n",pos);
	}
	return 0;
}	
