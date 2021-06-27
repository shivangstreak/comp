#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;scanf("%d",&n);
	int a[n];
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	int k;scanf("%d",&k);
	for(int i=0;i<n-k+1;i++){
		int L=a[i];
		for(int j=i+1;j<i+k;j++){
			if(a[j]>L){
				L=a[j];
			}
		}
		printf("%d ",L);
	}
	printf("\n");
	return 0;
}
