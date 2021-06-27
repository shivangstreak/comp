#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=500005;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		ll sum=0;
		int i;
		for(i=1;i*i<n;i++){
			if(n%i==0){
				sum+=i;
				sum+=n/i;
			}
		}
		if(i*i==n){
			sum+=i;
		}
		sum-=n;
		printf("%lld\n",sum);
	}
	return 0;
}
