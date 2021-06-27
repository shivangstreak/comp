#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e4+5;
ll phi[N];
int maxprime[N];
int main(){
	phi[1]=1;
	for(int i=2;i<=N;i++){
		if(maxprime[i]==0){
			for(int j=i<<1;j<=N;j+=i){
				maxprime[j]=i;
			}
		}		
	}
	for(int i=2;i<N;i++){
		if(maxprime[i]==0){
			phi[i]=i-1;
		}
		else{
			int q=i;
			int d=maxprime[i];
			while(q%d==0){
				q/=d;
			}
			phi[i]=phi[q]*(i/q)/d*(d-1);
		}
	}
	for(int i=2;i<=N;i++){
		phi[i]+=phi[i-1];
	}
	int n,t;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		printf("%lld\n",phi[n]*phi[n]);
	}
	return 0;
}
