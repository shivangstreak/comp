#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
int main(){
	int t;scanf("%d",&t);
	while(t--){
		priority_queue<ll>q;
		int n,k;scanf("%d%d",&n,&k);
		while(n--){
			ll d;scanf("%llu",&d);
			q.push(d);
		}
		ll sum=0;
		while(k--){
			ll s=q.top();
			sum+=s;
			q.pop();
			q.push(s/2);
		}
		printf("%llu\n",sum);
	}
	return 0;
}
