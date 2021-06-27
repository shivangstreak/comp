#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
struct node{
	int l,r;
}a[1000009];
bool cmp(const node &a,const node &b){
	if(a.l==b.l){
		return a.r<b.r;
	}
	else{
		return a.l<b.l;
	}
}
int BIT[1005];
int n,m,q;
void updatePoint(int indx){
	//indx++;
	while(indx<=m){
		BIT[indx]++;
		indx+=indx&(-indx);
	}
}
ll giveSum(int indx,ll ans){
	//indx++;
	while(indx>0){
		ans+=BIT[indx];
		indx-=indx&(-indx);
	}
	return ans;
}
int main(){
	int t,l,r;scanf("%d",&t);
	for(int j=1;j<=t;j++){
		memset(BIT,0,sizeof(BIT));
		scanf("%d%d%d",&n,&m,&q);
		for(int k=0;k<q;k++){
			scanf("%d%d",&l,&r);
			a[k].l=l;
			a[k].r=r;			
		}
		sort(a,a+q,cmp);
		ll ans=0;
		for(int k=0;k<q;k++){
			ans+=giveSum(m,0)-giveSum(a[k].r,0);
			updatePoint(a[k].r);
		}
		printf("Test case %d: %lld\n",j,ans);
	}
	return 0;
}
