#include <bits/stdc++.h> 
#define ll long long
using namespace std;
int countSetBits(ll n){
    int count = 0;
    while (n){
      n &= (n-1) ;
      count++;
    }
    return count;
}
int main(void){
  int t;cin>>t;
  while(t--){
  	int n;cin>>n;
  	ll a[n];
  	for(int i=0;i<n;i++)
  		cin>>a[i];
  	map<int,vector<int>>M;
	for(auto x:a){
		M[countSetBits(x)].push_back(x);
	}
	for(auto x:M){
		for(auto y:x.second){
			cout<<y<<" ";
		}
	}
	cout<<endl;
  }
}
