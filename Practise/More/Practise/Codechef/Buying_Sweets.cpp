#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,x;scanf("%d %d",&n,&x);
		int a[110];
		int sum=0;
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
			sum+=a[i];
		}
		int flag=0;
		int l=sum%x;
		for(int i=0;i<n;i++){
			if(a[i]<=l){
				flag=1;
				printf("-1\n");
				break;
			}
		}
		if(flag==0){
			printf("%d\n",sum/x);
		}
	}
	return 0;
}
