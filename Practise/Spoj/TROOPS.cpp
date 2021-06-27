#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct node{
	ll c,t,s;
	node(ll c1,ll t1,ll s1){
		c=c1;t=t1;s=s1;
	}
};
bool cmp(node a,node b){
	if(a.s>b.s){
		return true;
	}
	else{
		return false;
	}
}
int main(){
	int q;scanf("%d",&q);
	while(q--){
		int n;scanf("%d",&n);
		vector<node>v;
		ll mx=INT_MIN;
		for(int i=0;i<n;i++){
			ll c,t,s;scanf("%lld%lld%lld",&c,&t,&s);
			if(t>mx){
				mx=t;
			}
			v.push_back(node(c,t,s));
		}
		sort(v.begin(),v.end(),cmp);
		ll c=mx;
		ll sum=0;
		ll k=0;
		vector<node>:: iterator p;
		p=v.begin();
		while(c>0){
			
			/*p->t-=k;
			ll y=min(p->c,p->t);
			y=min(c,y);
			k+=y;*/
			k+=y;
			sum+=y*(p->s);
			c=c-y;
		}
		cout<<sum<<endl;
	}
	return 0;
}
