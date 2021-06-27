#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int d,n;scanf("%d",&n);
		int c=1,a[n];
		for(int i=0;i<n;i++)
			scanf("%d",&a[i]);
		for(int i=1;i<n;i++){
			if(a[i]>a[i-1]){
				a[i]=a[i-1];
			}
			else{
				c++;
			}
		}
		printf("%d\n",c);
		
	}
	return 0;
}
