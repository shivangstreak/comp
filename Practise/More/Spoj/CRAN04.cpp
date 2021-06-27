#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int main(){
	ll t,n,k;cin>>t;
	string str;
	vector<ll>index;
	while(t--){
		cin>>n>>k;
		cin>>str;
		ll total=0;
		index.clear();
		index.pb(-1);
		for(ll i=0;i<n;i++){
			if(str[i]=='1'){
				total++;
				index.pb(i);
			}
		}
		index.pb(n);
		if(k>total){
			printf("0\n");
			continue;
		}
		ll Count=0,temp,d,a,b;
		if(k==0){
			for(ll i=1;i<=total+1;i++){
				temp=index[i]-index[i-1]-1;
				Count+=(temp*(temp+1))/2;
			}
		}
		else{
			for(ll i=1;i<=total;i++){
				d=i+k-1;
				if(d>total){
					break;
				}	
				else{
					a=index[i]-index[i-1];
					b=index[d+1]-index[d];
					Count+=a*b;
				}
			}
		}
		cout<<Count<<"\n";
	}
	return 0;
}
