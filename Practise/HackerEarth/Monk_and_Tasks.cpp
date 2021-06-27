#include <bits/stdc++.h> 
#define ll unsigned long long
using namespace std;
ll countSetBits(ll n)
{
    ll count = 0;
    while (n)
    {
      n &= (n-1) ;
      count++;
    }
    return count;
}
int main(void)
{
  int t;cin>>t;
  while(t--){
  	int n;cin>>n;
  	ll a[n];
  	for(int i=0;i<n;i++)
  		cin>>a[i];
  	vector< pair<ll,ll> >v;
	for(auto x:a){
		v.push_back(make_pair(x,countSetBits(x)));
	}
	stable_sort(v.begin(),v.end(),[](pair<ll,ll>x,pair<ll,ll>y){ return x.second<y.second;});
	for(auto x:v){
		cout<<x.first<<" ";
	}	
  }
}
