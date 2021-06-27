#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll arr[100005];
int main(){
	int n,q;
	ll d;
	scanf("%d%d",&n,&q);
	for(int i=0;i<n;i++){
		scanf("%lld",&arr[i]);
	}
	sort(arr,arr+n);
	while(q--){
		scanf("%lld",&d);
		if(binary_search(arr,arr+n,d)){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}	
