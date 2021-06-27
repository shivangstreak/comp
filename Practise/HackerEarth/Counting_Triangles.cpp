#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
map< pair<pair<ll,ll>,ll>,int >mymap;
int main(){
	int n;
	scanf("%d",&n);
	ll A[3];
	int c=0;
	for(int i=0;i<n;i++){
		scanf("%lld%lld%lld",&A[0],&A[1],&A[2]);
		sort(A,A+3);
		mymap[{{A[0],A[1]},A[2]}]++;
	}
	for(auto x:mymap){
		if(x.second==1){
			c++;
		}
	}
	cout<<c<<"\n";
	return 0;
}	
