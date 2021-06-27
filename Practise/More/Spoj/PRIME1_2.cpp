#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
		int N=1000000009;
		vector<bool>v;
		for(int i=0;i<=N+1;i++){
			v.push_back(true);
		}
		v[0]=false;v[1]=false;
		for(int j=2;j<sqrt(N)+1;j++){
			if(v[j]==true)
				for(int k=j*j;k<N+1;k+=j){
					v[k]=false;
			}
		}
		vector<ll>primes;
		for(int i=2;i<=N+1;i++){
			if(v[i]==true)
				primes.push_back(i);
		}
		for(int i=1;i<=100;i++){
				if(v[i]==true){
					printf("%d\n",i);
				}
		}
	return 0;
}
