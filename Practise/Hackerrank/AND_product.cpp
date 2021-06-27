#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int main(){
	int t;scanf("%d",&t);
	ll a,b;
	while(t--){
		scanf("%lld%lld",&a,&b);
			int n=a^b;
			n|=n>>1;
			n|=n>>2;
			n|=n>>4;
			n|=n>>8;
			n|=n>>16;
			n|=n>>32;
			cout<< (a & ~n)<<"\n";
		
	}
	return 0;
}	
