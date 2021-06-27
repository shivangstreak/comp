#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define ll unsigned long long
ll modular_pow(ll base,ll exp){
	ll result=1;
	while(exp!=0){
		if(exp%2==1){
			result=(result*base)%MOD;
		}
		exp=exp>>1;  //same as exp/=2;
		base=(base*base)%MOD;
	}
	return result;
}
void multiply(ll F[2][2],ll M[2][2]){
	ll x=((F[0][0]*M[0][0])%MOD+(F[0][1]*M[1][0])%MOD)%MOD;
	ll y=((F[0][0]*M[0][1])%MOD+(F[0][1]*M[1][1])%MOD)%MOD;
	ll u=((F[1][0]*M[0][0])%MOD+(F[1][1]*M[1][0])%MOD)%MOD;
	ll z=((F[1][0]*M[0][1])%MOD+(F[1][1]*M[1][1])%MOD)%MOD;
	F[0][0]=x;F[0][1]=y;F[1][0]=u;F[1][1]=z;
}
void power(ll F[2][2],ll n){
	if(n==0 || n==1){
		return;
	}
	ll M[2][2]={{1,1},{1,0}};
	power(F,n/2);
	multiply(F,F);
	if(n%2==1){
		multiply(F,M);
	}
}
ll nth_fib(ll n){
	ll F[2][2] = {{1,1},{1,0}};
 	if (n == 0)
    		return 0;
  	power(F, n-1);
  	if(F[0][0]<0){
  		return F[0][0]+=MOD;
  	}
  	else return F[0][0]%MOD;
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%llu",&n);
		if(n==0){
			printf("0\n");
			continue;
		}
		printf("%llu\n",(( (nth_fib(2*n)%MOD) * (nth_fib(2*n+1)%MOD) )%MOD - nth_fib(4*n+3)%MOD)%MOD );
	}
	return 0;
}
