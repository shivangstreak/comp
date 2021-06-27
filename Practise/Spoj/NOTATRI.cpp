#include<bits/stdc++.h>
using namespace std;
#define pb push_back
int a[2005];
#define ll long long
int main(){
	int n;scanf("%d",&n);
	while(n!=0){
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
		}
		sort(a,a+n);
		ll count=0;
		for(int k=n-1;k>1;k--){
			int i=0,j=k-1;
			while(i<j){
				if(a[k]>a[i]+a[j]){
					count+=j-i;
					i++;
				}	
				else{
					j--;
				}
			}
		}	
		printf("%lld\n",count);
		scanf("%d",&n);	
	}
	return 0;
}
