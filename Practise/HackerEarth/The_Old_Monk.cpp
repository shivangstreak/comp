#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
ll A[N],B[N];
int main(){
	int n,t;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%lld",&A[i]);
		}
		for(int i=0;i<n;i++){
			scanf("%lld",&B[i]);
		}
		int start,mid,end,pos,ans=0;
		for(int i=0;i<n;i++){
			start=0;
			end=n-1;
			pos=-1;
			while(start<=end){
				mid=(start+end)>>1;
				if(B[mid]>=A[i]){
					pos=mid;
					start=mid+1;
				}
				else{
					end=mid-1;
				}
			}
			ans=max(ans,pos-i);
		}
		printf("%d\n",ans);
	}
	return 0;
}	
