#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
ll arr[105];
int rightMostSetBit(ll x){
	int k=-1;
	while(x!=0){
		x=x>>1;
		k++;
	}
	return k;
}
int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%lld",&arr[i]);
	}
	ll *p,*q;
	p=arr;
	sort(p,p+n);
	int m=n>>1;
	int k=rightMostSetBit(p[m]);
	while(k>=0){
		int x=1<<k;
		for(int i=0;i<n;i++)
			q[i]=p[i]^x;
		sort(p,p+n);
		int s=rightMostSetBit(p[m]);
		if(s==k){
			break;
		}
		swap(p,q);
		k=s;
	}
	printf("%d\n",k);
	return 0;
}	
