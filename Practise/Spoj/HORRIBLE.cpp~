#include<bits/stdc++.h>  // Range Update ans range Query using 2 BITs ....
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
ll BIT1[100005],BIT2[100005];
ll giveSum(ll *arr,int indx){
	ll ans=0;
	while(indx>0){
		ans+=arr[indx];
		indx-=indx&(-indx);
	}
	return ans;
}
void update(ll *arr,int indx,ll val,int len){
	while(indx<=len){
		arr[indx]+=val;
		indx+=indx&(-indx);
	}
}
void updateRange(int l,int r,ll val,int len){
	update(BIT1,l,val,len);
	update(BIT1,r+1,-val,len);
	update(BIT2,l,val*(l-1),len);
	update(BIT2,r+1,-val*r,len);
}
ll query(int indx){
	return giveSum(BIT1,indx)*indx-giveSum(BIT2,indx);
}
ll queryRange(int l,int r){
	return query(r)-query(l-1);
}
int main(){
	int n,c,x,l,r,t,val;scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&c);
		memset(BIT1,0,sizeof(BIT1));
		memset(BIT2,0,sizeof(BIT2));		
		while(c--){
			scanf("%d",&x);
			if(x==0){
				scanf("%d%d%d",&l,&r,&val);
				updateRange(l,r,val,n);
			}
			else{
				scanf("%d%d",&l,&r);
				printf("%lld\n",queryRange(l,r));
			}
		}
	}
	return 0;
}
