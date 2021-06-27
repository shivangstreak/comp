#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
ll arr[N];
int even[N],odd[N];
int main(){
	int n,t;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		fill(even,even+n+4,0);
		fill(odd,odd+n+4,0);
		int o=0,e=0;
		for(int i=0;i<n;i++)
			scanf("%lld",&arr[i]);
		for(int i=n-1;i>=0;i--){
			if(arr[i]&1){
				o++;
				even[i]=e;
			}
			else{
				e++;
				odd[i]=o;
			}
		}
		ll sum=0;
		for(int i=0;i<n;i++){
			if(arr[i]&1){
				sum+=even[i];
			}
			else{
				sum+=odd[i];
			}
		}
		printf("%lld\n",sum);
	}
	return 0;
}	
