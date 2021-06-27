#include<bits/stdc++.h> // Binary-search ... 
using namespace std;
#define pb push_back 
#define ll long long
int a[105];
int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	vector<int>v1,v2;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++){
				v1.pb((a[i]*a[j])+a[k]);
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			for(int k=0;k<n;k++){
				if(a[k]!=0){
					v2.pb((a[i]+a[j])*a[k]);
				}
			}
		}
	}
	ll ans=0;
	ll low,high;
	sort(v1.begin(),v1.end());
	sort(v2.begin(),v2.end());
	for(auto x:v1){
		low=lower_bound(v2.begin(),v2.end(),x)-v2.begin();
		high=upper_bound(v2.begin(),v2.end(),x)-v2.begin();
		ans+=high-low;
	}
	printf("%lld\n",ans);
	return 0;
}
