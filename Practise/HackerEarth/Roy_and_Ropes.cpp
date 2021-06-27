#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e6+5;
ll lo[N],up[N];
int main(){
	int l,t;scanf("%d",&t);
	while(t--){
		scanf("%d",&l);
		for(int i=1;i<=l-1;i++){
			scanf("%lld",&lo[i]);
		}
		for(int i=1;i<=l-1;i++){
			scanf("%lld",&up[i]);
		}
		ll curr=0;
		ll mx;
		for(int i=l-1;i>=1;i--){
			curr++;
			mx=max(lo[i],up[i]);
			if(i!=1 && curr<mx){
				curr+=(mx-curr);
			}
			if(i==1){
				if(mx>curr && (mx-curr)>1){
					curr+=(mx-curr);
					curr++;
				}
				else{
					curr++;
				}
			}
		}
		printf("%lld\n",curr);
	}
	return 0;
}	
