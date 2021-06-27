#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	int a[100052];
	while(t--){
		int c=0;
		int n;scanf("%d",&n);
		memset(a,0,sizeof(a));
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
		}
		if(n>=1 && a[0]!=a[1]){
			c++;
		}
		for(int i=1;i<n-1;i++){
			if(a[i-1]!=a[i] || a[i]!=a[i+1]){
				c++;
			}
		}
		if(n>=1 && a[n-1]!=a[n-2]){
			c++;
		}
		printf("%d\n",c);
	}
	return 0;
}
