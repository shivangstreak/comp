#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=2*1e5+5;
ll arr[N];
int BITS[N];
int n;
void update(int indx,int val){
	while(indx<=n){
		BITS[indx]+=val;
		indx+=indx&(-indx);
	}
}
ll giveSum(int indx){
	ll ans=0;
	while(indx>0){
		ans+=BITS[indx];
		indx-=indx&(-indx);
	}
	return ans;
}
bool chk(ll d){
	if(d<0){
		return false;
	}
	if(d<10){
		return true;
	}	
	ll j=d;
	while(d/10!=0){
		d=d/10;
	}
	if(j%10==d){
		return true;
	}		
	else{
		return false;
	}
}
int main(){
	int q,d,l,r,i;
	ll k;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>arr[i];
		if(chk(arr[i])==true){
			update(i,1);
		}
	}
	while(q--){
		scanf("%d\n",&d);
		if(d==1){
			cin>>l>>r;
			printf("%lld\n",giveSum(r)-giveSum(l-1));
		}
		else{
			//cout<<"d is 2"<<endl;
			cin>>i>>k;
			//cout<<"i & k "<<i<<" "<<k<<endl;
			bool a=chk(arr[i]),b=chk(k);
			if(a==true && b==false){
				update(i,-1);
			}
			else if(a==false && b==true){
				update(i,1);
			}
			arr[i]=k;
		}
	}
	return 0;
}
