#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
ll H[N];
int main(){
	int t,n,k;scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		for(int i=0;i<n;i++){
			scanf("%lld",&H[i]);
		}
		ll mx=0,curr=0;
		for(int i=0;i<n;i++){
			if(H[i]<=k){
				curr=curr+H[i];
				mx=max(curr,mx);
			}
			else{
				curr=0;
			}
		}
		printf("%lld\n",mx);
	}
	return 0;
}	
