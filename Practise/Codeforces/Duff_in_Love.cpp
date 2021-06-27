#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll n;cin>>n;
	for(ll i=2;i*i<=n;i++){
		/*cout<<"n "<<n<<"\n";
		cout<<"i "<<i<<" ";*/
		if(n%(i*i)==0){
			n/=i;
			i=1;
		//	cout<<endl;
		}
	}
	cout<<n<<"\n";
	return 0;
}
