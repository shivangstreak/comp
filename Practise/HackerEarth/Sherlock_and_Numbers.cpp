#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll arr[100005];
int main(){
	int t,n,k,p;
	scanf("%d",&t);
	while(t--){
		scanf("%d%d%d",&n,&k,&p);
		if(k==0){
			printf("%lld\n",(ll)p);
			continue;
		}
		arr[0]=0;
		for(int i=1;i<=k;i++)
			scanf("%lld",&arr[i]);
		arr[k+1]=n+1;
		if(p>n-k){
			printf("-1\n");
			continue;
		}	
		sort(arr,arr+k);
		for(int i=1;i<=k+1;i++){
			int d=arr[i]-arr[i-1]-1;
			if(p-d<=0){
				printf("%lld\n",arr[i-1]+(ll)p);
				break;
			}
			else{
				p-=d;
			}
		}
	}
	return 0;
}
