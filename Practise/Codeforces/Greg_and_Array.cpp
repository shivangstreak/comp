#include<bits/stdc++.h> //BIT Count is a BIT which stores the frequency....!!!  
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
struct node{
	int l,r;
	ll val;
};
const int N=1e5+5;
ll BIT[N];
int A[N];
node M[N];
ll Count[N];
void update(ll *arr,int indx,ll val,int len){
	while(indx<=len){
		arr[indx]+=val;
		indx+=indx&(-indx);
	}
}
void updateRange(ll *arr,int l,int r,ll val,int len){
	update(arr,l,val,len);
	update(arr,r+1,-1*val,len);
}
ll giveSum(ll *arr,int indx){
	ll ans=0;
	while(indx>0){
		ans+=arr[indx];
		indx-=indx&(-indx);
	}
	return ans;
}
int main(){
	int a,b,d,l,r,val,n,m,k;scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);	
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&l,&r,&val);
		M[i].l=l;
		M[i].r=r;
		M[i].val=val;
	}
	while(k--){
		scanf("%d%d",&l,&r);
		//cout<<"lol "<<l<<" "<<r<<endl;
		updateRange(Count,l,r,1,m);
	}
	for(int i=1;i<=m;i++){
		l=M[i].l;
		r=M[i].r;
		val=M[i].val;
		ll CC=giveSum(Count,i);
		//cout<<CC<<endl;
		updateRange(BIT,l,r,val*CC,n);
	}
	for(int i=1;i<=n;i++){
		//printf("%I64d ",A[i]+giveSum(BIT,i));
		cout<<A[i]+giveSum(BIT,i)<<" ";
	}
	printf("\n");
	return 0;
}
