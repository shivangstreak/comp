#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll gcd(ll a,ll b){
	ll x=min(a,b);
	ll y=max(a,b);
	if(x==0){
		return y;
	}
	else{
		return gcd(x,y%x);
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		string str;cin>>str;
		ll len=str.size();
		ll Count=0;
		int flag=0;
		for(ll i=len-1;i>=0;i--){
			if(str[i]=='.'){
				flag=1;
				break;
			}
			else{
				Count++;
			}
		}
		ll u=1;
		for(ll i=0;i<Count;i++){
			u*=10;
		}
		ll o=0;
		for(ll i=0;i<len;i++){
			if(str[i]=='.')
				continue;
			o*=10;
			o+=str[i]-'0';
		}
		ll p=1;
		if(flag==1){
			p=gcd(u,o);
			cout<<u/p<<"\n";	
		}
		else{
			printf("1\n");
		}
	}
	return 0;
}
