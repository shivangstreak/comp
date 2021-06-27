#include<bits/stdc++.h>
using namespace std;
#define ll long long
int const N=200005;
ll b[N];
int main(){
	int n;
	ll c=0;
	int x=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>b[i];
		c+=abs(x-b[i]);
		x=b[i];
	}
	cout<<c<<endl;
	return 0;
}
