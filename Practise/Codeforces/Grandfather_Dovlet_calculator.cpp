#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int x[]={6,2,5,5,4,5,6,3,7,6};
const int N=1e6+1;
int arr[N+5];
int main(){
	faster;
	int a,b;
	for(int i=0;i<=N;i++){
		if(i<10){
			arr[i]=x[i];
		}
		else{
			arr[i]=arr[(i/10)]+x[(i%10)];
		}
	}
	cin>>a>>b;
	ll sum=0;
	for(int i=a;i<=b;i++){
		sum+=arr[i];
	}
	cout<<sum<<"\n";
	return 0;
}
