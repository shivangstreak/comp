#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int a[N];
int D2[N],D1[N];
int main(){
	int n;scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=0;i<n;i++){
		D1[i]=1;
	}
	for(int i=0;i<n;i++){
		D2[i]=1;
	}
	for(int i=0;i<n-1;i++){
		if(a[i]<a[i+1]){
			D1[i+1]+=D1[i];
		}
	}
	for(int i=n-1;i>0;i--){
		if(a[i-1]>a[i]){
			D2[i-1]+=D2[i];
		}
	}
	int sum=0;
	for(int i=0;i<n;i++){
		sum+=max(D1[i],D2[i]);
	}
	cout<<sum<<"\n";
    return 0;
}
