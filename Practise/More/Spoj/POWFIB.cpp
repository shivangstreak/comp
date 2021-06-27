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
int nth_nonFib(int n){
	int ans;
	 int a=1,b=2,c=3;
              while(n>0){
               a=b;
               b=c;
               c=a+b;
               n-=(c-b-1);
              }
              n+=(c-b-1);
              ans=b+n;
     return ans;      
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
	ll t;scanf("%llu",&t);
	while(t--){
		ll n;scanf("%llu",&n);
		//cout<<nth_fib(n)<<" "<<nth_nonFib(n)<<endl;
		printf("%llu\n",modular_pow(nth_nonFib(n),nth_fib(n)));
	}
	return 0;
}
