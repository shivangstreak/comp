#include<bits/stdc++.h>
using namespace std;
int c[150],sum[150];
int main(){
	int n;scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&c[i]);
	}
	int x,y;scanf("%d%d",&x,&y);
	sum[1]=c[1];
	for(int i=2;i<=n;i++){
		sum[i]=sum[i-1]+c[i];
	}
	for(int i=1;i<=n;i++){
		if(sum[i]>=x && sum[i]<=y && sum[n]-sum[i]>=x && sum[n]-sum[i]<=y){
			printf("%d\n",i+1);
			return 0;
		}
	}
	printf("0\n");
	return 0;
}
