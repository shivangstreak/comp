#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=5*1e5+5;
const int MOD=1e9+7;
int a[N];
int modular_exp(int base,int exp){
	int res=1;
	while(exp!=0){
		if(exp&1){
			res=(1LL * res * base)%MOD;
		}
		exp=exp>>1;
		base=(1LL * base * base)%MOD;
	}
	return res;
}
int main(){
	int n,q,u,v;
	int k;
	char ch[2];
	scanf("%d%d",&n,&q);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	sort(a,a+n);
	while(q--){
		scanf("%s",ch);
		scanf("%d",&k);
		if(ch[0]=='='){
			u=upper_bound(a,a+n,k-1)-a;
			v=upper_bound(a,a+n,k)-a;
			int ans=modular_exp(2,v)-modular_exp(2,u);
			if(ans<0)
				ans+=MOD;
			printf("%d\n",ans);
		}
		else if(ch[0]=='<'){
			k--;
			u=upper_bound(a,a+n,k)-a;
			printf("%d\n",modular_exp(2,u));			
		}
		else if(ch[0]=='>'){
			u=upper_bound(a,a+n,k)-a;
			int ans=modular_exp(2,n)-modular_exp(2,u);
			if(ans<0){
				ans+=MOD;
			}
			printf("%d\n",ans);
		}
	}
	return 0;
}
