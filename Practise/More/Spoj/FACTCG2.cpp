#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e7+5;
int minPrime[N];
void seive(){	
	for(int i=2;i*i<=N;i++){
		if(minPrime[i]==0){
			for(int j=i*i;j<=N;j+=i){
				if(minPrime[j]==0){
					minPrime[j]=i;
				}
			}
		}
	}
	for(int i=2;i<=N;i++){
		if(minPrime[i]==0)
			minPrime[i]=i;
	}
}
int main(){
	seive();
	int n,dummy;
	while(scanf("%d",&n)==1){
		if(n==1){
			printf("1\n");
			continue;
		}
		printf("1 x ");
		
		while(n!=1){
			dummy=minPrime[n];
			n/=minPrime[n];
			if(n!=1)
				printf("%d x ",dummy);
			else{
				printf("%d\n",dummy);
			}	
		}
	}
	return 0;
}
