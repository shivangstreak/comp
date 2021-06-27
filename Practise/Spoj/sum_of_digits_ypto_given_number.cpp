#include<bits/stdc++.h>
using namespace std;
int sod(int N){
	if(N<=9){
		return N*(N+1)/2;
	}
	int i=0;
	int n=N;
	while(n/10!=0){
		i++;
		n/=10;
	}
	int p=pow(10,i);
	cout<<"p "<<p<<"\n";
	return ((n*i*45*p/10)+(n*(n-1)*p/2)+n*(N%p+1)+sod(N%p));
}
int main(){
	int n;cin>>n;
	cout<<sod(n)<<endl;
	return 0;
}
