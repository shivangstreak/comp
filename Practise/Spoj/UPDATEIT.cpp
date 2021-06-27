#include<bits/stdc++.h>// Range update point query
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
int BIT[10005];
void update(int indx,int val,int len){
	while(indx<=len){
		BIT[indx]+=val;
		indx+=indx&(-indx);
	}
}
void updateRange(int l,int r,int val,int len){
	update(l,val,len);
	update(r+1,-val,len);
}
int giveValue(int indx,int len){
	int ans=0;
	while(indx>0){
		ans+=BIT[indx];
		indx-=indx&(-indx);
	}
	return ans;
}
int main(){
	int n,u,q,l,r,val,t;scanf("%d",&t);
	while(t--){
		memset(BIT,0,sizeof(BIT));
		scanf("%d%d",&n,&u);
		while(u--){
			scanf("%d%d%d",&l,&r,&val);
			updateRange(l+1,r+1,val,n);
		}
		scanf("%d",&q);
		while(q--){
			scanf("%d",&l);
			l++;
			printf("%d\n",giveValue(l,n));	
		}
	}
	return 0;
}
