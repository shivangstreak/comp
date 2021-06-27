#include<bits/stdc++.h> //Binary Indexed Tree...
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
const int N=2*1e5+6;
int a[N],b[N];
pair<int,int>pair_arr[N];
int BIT[N];
ll BIT_for_ans[N];
int n,q;
ll giveSum2(int indx,ll ans){
	//cout<<"processing "<<indx<<endl;	
	indx++;
	while(indx>0){
		ans+=BIT_for_ans[indx];
		indx-=indx&(-indx);
	}
	return ans;
}
void updateBit2(int indx,ll val){
	indx++;
	while(indx<=n){
		BIT_for_ans[indx]+=val;
		indx+=indx&(-indx);
	}
}
ll giveSum(int indx,ll ans){
	//cout<<"processing "<<indx<<endl;	
	indx++;
	while(indx>0){
		ans+=BIT[indx];
		indx-=indx&(-indx);
	}
	return ans;
}
void updateBit(int indx,ll val){
	indx++;
	while(indx<=n){
		BIT[indx]+=val;
		indx+=indx&(-indx);
	}
}
void rangeUpdate(int l,int r){
	//cout<<"range update "<<l<<" "<<r<<endl;
	updateBit(l,1);
	updateBit(r+1,-1);
}
int main(){
	int l,r;
	scanf("%d%d",&n,&q);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	sort(a,a+n);
	reverse(a,a+n);
	for(int k=0;k<q;k++){
		scanf("%d%d",&l,&r);
		l--,r--;
		pair_arr[k]={l,r};
		rangeUpdate(l,r);
	}
	priority_queue<pair<ll,int>>Q;
	for(int i=0;i<n;i++){
		Q.push({giveSum(i,0),i});
	}
	int k=0;
	while(Q.empty()==false){
		pair<ll,int> top=Q.top();
		Q.pop();
		b[top.second]=a[k];
		k++;
	}
	ll ans=0;
	for(int i=0;i<n;i++){
		updateBit2(i,b[i]);
	}
	for(int k=0;k<q;k++){
		l=pair_arr[k].first;
		r=pair_arr[k].second;
		ans+=giveSum2(r,0)-giveSum2(l-1,0);
	}
	//cout<<ans<<endl;
	printf("%I64d\n",ans);
	return 0;
}
