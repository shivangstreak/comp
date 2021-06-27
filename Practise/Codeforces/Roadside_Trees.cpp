#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll unsigned long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
const int N=1e5+6;
int a[N];
int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	ll sum=0,c;
	for(int i=0;i<n;i++){
		if(i==0){
			sum+=a[i]+1;	
		}
		else{
			sum+=abs(a[i]-a[i-1])+2;
		}
	}
	cout<<sum<<"\n";
	return 0;
}
