#include<bits/stdc++.h>
using namespace std;
#define ll long long
bool isPrime(int a){  // Use this to chk if a number is prime or not....
	if(a<=3){
		if(a>1)
			return true;
		else
			return false;	
	}
	if(a%2==0||a%3==0)
		return false;
	else{
		for(int i=5;i*i<a;i+=6){
			if(a%i==0)
				return false;
		}
		return true;
	}	
}
int countSetBits(ll n){
    int count = 0;
    while (n){
      n &= (n-1) ;
      count++;
    }
    return count;
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		ll a,b;cin>>a>>b;
		int c=0;
		for(ll i=a;i<=b;i++){
			if(isPrime(countSetBits(i))){
				c++;
			}
		}
		cout<<c<<"\n";
	}
	return 0;
}
