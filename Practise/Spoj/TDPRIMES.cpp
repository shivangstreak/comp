#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e8+5;
const int MAX=1e8;
const int LIM=sqrt(N)+1;
int prime[N>>6];
#define isPrime(x) (prime[x>>6]&(1<<((x>>1)&31)))
#define set(x) (prime[x>>6]|=(1<<((x>>1)&31)))
void seive(){
	register int i,j,k;
	for(i=3;i<=LIM;i+=2){
		if(!isPrime(i)){
			for(j=i*i,k=i<<1;j<N;j+=k){
				set(j);
			}
		}
	}
}
int main(){
	seive();
	int c=1;
	printf("2\n");
	for(int i=3;i<MAX;i+=2){
		if(!isPrime(i)){
			c++;
			if(c%100==1){
				printf("%d\n",i);
			}
		}
	}
	return 0;
}
