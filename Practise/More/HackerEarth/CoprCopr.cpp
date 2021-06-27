#include<bits/stdc++.h>  //Euler's totient function 
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e7+5;
int prime[N];
int phi[N];
ll pre_sum[N];
int main(){
	int t;
	scanf("%d",&t);
	prime[0]=1;
	prime[1]=1;
	for(int i=2;i<=N;i++){
		if(prime[i]==0){
			for(int j=2*i;j<=N;j+=i){
				prime[j]=i;
			}
		}
	}
	phi[1]=1;
	for(int i=2;i<=N;i++){
		if(prime[i]==0){
			phi[i]=i-1;
		}
		else{
			int d=i;
			int max_prime=prime[i];
			while((d%max_prime)==0){
				d/=max_prime;
			}
			phi[i]=phi[d]*(i/d)/max_prime*(max_prime-1);	
		}
	}
	for(int i=1;i<=N;i++){
		pre_sum[i]=pre_sum[i-1]+phi[i];
	}
	while(t--){
		int h;scanf("%d",&h);
		cout<<pre_sum[h]<<"\n";
	}
	return 0;
}
