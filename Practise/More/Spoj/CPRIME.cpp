#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e8+5;
const int LIM=sqrt(N)+1;
int prime[N>>6];
int pre_sum[N];
#define ifPrime(x) (prime[x>>6]&(1<<((x>>1)&31))) 
#define set(x) (prime[x>>6]|=(1<<((x>>1)&31))) 
void seive(){
	register int i,j,k;
	for(i=3;i<=LIM;i+=2){
		if(!ifPrime(i)){
			for(j=i*i,k=i<<1;j<N;j+=k){
				set(j);
			}	
		}
	}
}
int main(){
	int n;
	double ans;
	seive();
	pre_sum[2]=1;
	for(int i=3;i<N;i++){
		if(i&1 && !ifPrime(i)){
			pre_sum[i]=pre_sum[i-1]+1;
		}
		else{
			pre_sum[i]=pre_sum[i-1];
		}
	}
	while(true){
		scanf("%d",&n);
		if(n==0)
			break;
		double ans=(double)n;
		ans/=log(n);
		ans=fabs(pre_sum[n]-(ans)) / ((double)pre_sum[n]);
		printf("%.1lf\n",ans*100);
	}
	return 0;
}
