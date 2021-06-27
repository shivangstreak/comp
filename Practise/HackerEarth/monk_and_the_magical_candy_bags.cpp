#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;cin>>t;
	while(t--){
		int n,k;cin>>n>>k;
		vector<ll>v;
		ll a;
		for(int i=0;i<n;i++){
			cin>>a;
			v.push_back(a);
		}
		vector<ll>::iterator it;
		ll sum=0;
		for(int i=0;i<k;i++){
			it=max_element(v.begin(),v.end());
			sum+=(*it);
			ll temp=(*it)/2;
			v.erase(it);
			v.push_back(temp);
		}
		cout<<sum<<endl;
	}
}

