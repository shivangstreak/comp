#include<bits/stdc++.h>
using namespace std;
#define ll long long int
int a[1010];
int main(){
	int n,l;
	scanf("%d%d",&n,&l);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	sort(a,a+n);
	int mx=INT_MIN;
	mx=2*max(a[0],l-a[n-1]);
	for(int i=0;i<n-1;i++){
		mx=max(mx,a[i+1]-a[i]);
	}
	printf("%.10f\n",mx/2.0);
	return 0;
}
