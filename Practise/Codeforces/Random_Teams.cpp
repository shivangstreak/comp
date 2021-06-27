#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long int
int main(){
	ll n,m;
	cin>>n>>m;
	if(m==1){
		ll o=(n*(n-1))/2;
		cout<<o<<" "<<o<<"\n";
		return 0;
	}
	ll mx,mn,x,y;
  	  n=n-m;
   	 mx=n*(n+1)/2;
   	 x=1;
   	 x=x+n/m;
   	 y=n%m;
   	 mn=(y*(x+1)*x)/2+((m-y)*x*(x-1))/2;
	cout<<mn<<" "<<mx<<"\n";
	return 0;
}
