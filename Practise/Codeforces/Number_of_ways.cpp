#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
const int N=5*1e5+6;
int a[N];
ll SUM[N];
int b[N];
int b_sum[N];
int main(){
	int n;scanf("%d",&n);
	ll d=0;
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		d+=a[i];
	}
	if(d%3!=0){
		printf("0\n");
		return 0;
	}
	SUM[n-1]=a[n-1];
	if(SUM[n-1]==d/3){
		b[n-1]=1;
	}
	b_sum[n-1]=b[n-1];
	for(int i=n-2;i>=0;i--){
		SUM[i]=SUM[i+1]+a[i];
		if(SUM[i]==d/3){
			b[i]=1;
		}
		b_sum[i]=b_sum[i+1]+b[i];
	}
	ll temp=0;	
	int start;
	ll ans=0;
	for(start=0;start<=n-3;start++){
		temp+=a[start];
		if(temp==d/3){
			if(start+2<n){
				ans+=b_sum[start+2];		
			}
		}
	}
	cout<<ans<<"\n";
	return 0;
}
