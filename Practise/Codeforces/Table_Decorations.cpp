#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	ll a[3];
	cin>>a[0]>>a[1]>>a[2];
	//scanf("%d%d%d",&a[0],&a[1],&a[2]);
	sort(a,a+3);
	if(2*(a[0]+a[1])<=a[2]){
		//cout<<"Here\n";
		cout<<a[0]+a[1]<<"\n";
	}
	else{
		//cout<<"There\n";
		cout<<(a[0]+a[1]+a[2])/3<<"\n";
	}
	return 0;
}
