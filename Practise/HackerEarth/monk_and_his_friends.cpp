#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;scanf("%d",&t);
	while(t--){
		multiset<ll>my;
		ll a,b;
		int n,m;scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++){
			scanf("%lld",&a);
			my.insert(a);
		}
		for(int j=0;j<m;j++){
			scanf("%lld",&b);
			if(my.find(b)!=my.end()){
				printf("YES\n");
			}
			else{
				printf("NO\n");
			}
			my.insert(b);
		}
	}
	return 0;
}
