#include<bits/stdc++.h>
using namespace std;
bool check(int n){
	int m=n;
	int r=0;
	while(n!=0){
		r=r*10+(n%10);
		n/=10;
	}
	return m==r;
}
int main(){
	int t;cin>>t;
	while(t--){
		int n,m,c=0;cin>>n>>m;
		for(int i=n;i<=m;i++){
			if(check(i))
				c++;
		}
		cout<<c<<endl;
	}
	return 0;
}
