#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e7+5;
int arr[N];
int minPrime[N];
int div(int n){
	ll pro=1;
	map<int,int>mymap;
	mymap.clear();
	//cout<<n<<endl;
	for(int i=2;i*i<=n;i++){
		while(n%i==0){
			mymap[i]++;
			n/=i;
		}
	}
	if(n!=1){
		mymap[n]++;
	}
	for(auto x:mymap){
		//cout<<x.first<<" "<<x.second<<endl;
		pro*=(x.second+1);
	}
	return pro;
}
int main(){
	//faster;
	int n;cin>>n;
	for(int i=0;i<n;i++){
		cin>>arr[i];
	}
	for(int i=0;i<n;i++){
		if(div(arr[i])>=4){
			cout<<"YES\n";
		}
		else{
			cout<<"NO\n";
		}
	}
	return 0;
}
