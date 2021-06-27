#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+5;
ll BIT[N],arr[N];
int n;
ll dp[N];
void update(int x,int val){
	while(x<=n){
		BIT[x]+=val;
		x+=x&(-x);
	}
}
ll query(int x){
	ll ans=0;
	while(x>0){
		ans+=BIT[x];
		x-=x&(-x);
	}
	return ans; 
}
void updateRange(int l,int r){
	update(l,1);
	update(r+1,-1); 
}
int main(){
	int m1,x,l,r,m,q,j=0;
	scanf("%d",&n);
	scanf("%d",&m);
	m1=m;
	while(m--){
		scanf("%d%d",&l,&r);
		updateRange(l,r);
	}
	// how many boxes are there with i coins dp[i]..
	for(int i=1;i<=n;i++){
		dp[(query(i))]++;
	}
	for(int i=m1-1;i>=0;i--){
		dp[i]+=dp[i+1];
	}
	/*cout<<"LOL\n";
	for(int i=0;i<=m1;i++){
		cout<<i<<" "<<dp[i]<<"\n";
	}
	cout<<"end\n";*/
	scanf("%d",&q);
	while(q--){
		scanf("%d",&x);
		printf("%lld\n",dp[x]);	
	}
	return 0;
}	
