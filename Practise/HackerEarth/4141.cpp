#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=5*1e4+5;
int arr[N];
int n;
bool solve(){
	int p=1;
	int ans=a[0];
	for(int i=1;i<n;i++){
		ans=((ans*10)%41+(arr[i]%41))%41;
	}
	if(ans==0){
		return true;
	}
	else{
		return false;
	}
}
int main(){
	faster;
	int t,c;cin>>t;
	while(t--){
		cin>>arr[0]>>arr[1]>>c>>n;
		if(n==1){
			if(arr[0]==0)
				cout<<"YES\n";
			else{
				cout<<"NO\n";
			}	
			continue;
		}
		for(int i=2;i<n;i++){
			arr[i]=(arr[i-1]*c+arr[i-2]);
			if(arr[i]>=10){
				arr[i]=arr[i]%10;
			}
			else if(arr[i]<0)
				arr[i]+=10;
		}
		if(solve()){
			cout<<"YES\n";
		}
		else{
			cout<<"NO\n";
		}
	}
	return 0;
}
