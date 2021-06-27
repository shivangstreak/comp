#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const int N=1e5+5;
int a[N];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&a[i]);
	}
	ll sum=a[1]-1;
	for(int i=2;i<=m;i++){
		if(a[i-1]<a[i]){
	//		cout<<"greater ";
	//		cout<<a[i-1]<<" "<<a[i]<<endl;
			sum+=a[i]-a[i-1];
		}
		else if(a[i-1]>a[i]){
			//cout<<"less ";
			//cout<<a[i-1]<<" "<<a[i]<<endl;
			sum+=n+a[i]-a[i-1];
		}
	}
	cout<<sum<<"\n";
	return 0;
}
