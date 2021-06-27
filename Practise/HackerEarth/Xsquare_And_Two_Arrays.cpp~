#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll unsigned long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
ll A[N],B[N],AA[N],BB[N];
int main(){
	faster;
	int n,q,d,l,r;
	cin>>n>>q;
	for(int i=1;i<=n;i++){
		cin>>A[i];
		if(i>=3){
			A[i]+=A[i-2];
		}
	}
	for(int i=1;i<=n;i++){
		cin>>B[i];
		if(i>=3){
			B[i]+=B[i-2];
		}
	}
	while(q--){
		cin>>d>>l>>r;
		ll sum;
		if(d==1){
			sum=0;
			if( (r%2==1 && l%2==1) || (r%2==0 && l%2==0) ){
				if(l==1){
					sum+=A[r];
				}
				else{
					sum+=A[r]-A[l-2];
				}
				sum+=B[r-1]-B[l-1];
			}
			else{
				if(l==1){
					sum+=A[r-1];
				}
				else{
					sum+=A[r-1]-A[l-2];
				}
				sum+=B[r]-B[l-1];
			}
		}
		else{
			sum=0;
			if( (r%2==1 && l%2==1) || (r%2==0 && l%2==0) ){
				if(l==1){
					sum+=B[r];
				}
				else{
					sum+=B[r]-B[l-2];
				}
				sum+=A[r-1]-A[l-1];
			}
			else{
				if(l==1){
					sum+=B[r-1];
				}
				else{
					sum+=B[r-1]-B[l-2];
				}
				sum+=A[r]-A[l-1];
			}
		}	
		cout<<sum<<"\n";
	}
	return 0;
}	
