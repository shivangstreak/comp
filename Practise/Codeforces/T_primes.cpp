#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
const int N=1e5+5;
ll a[N];
int prime[1200001];
bool is_sqr(ll i){
	ll x=sqrt(i);
	return (x*x==i && prime[x]==1);
}
int main(){
	int n;scanf("%d",&n);
	memset(prime,1,sizeof(prime));
	prime[1]=0;
	prime[0]=0;
	for (int i=2;i<=1200000;i++){
		if (prime[i]==0) continue;
		prime[i]=1;
		for (int j=2;j*i<1200000;j++){
			prime[i*j]=0;
		}
	}	
	for(int i=0;i<n;i++){
		//scanf("%d",&a[i]);
		cin>>a[i];	
	}
	for(int i=0;i<n;i++){
		if(is_sqr(a[i])){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}
