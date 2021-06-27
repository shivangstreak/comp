#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int n;scanf("%d",&n);
	int x[n],y[n];
	for(int i=0;i<n;i++){
		scanf("%d%d",&x[i],&y[i]);	
	}
	if(n==1){
		printf("-1\n");
	}
	else if(n==2){
		if(x[0]==x[1] || y[0]==y[1]){
			printf("-1\n");
		}
		else{
			printf("%d\n",(abs(y[1]-y[0])*abs(x[1]-x[0])));
		}
	}
	else{
		int a=abs(x[0]*(y[1]-y[2])+x[1]*(y[2]-y[0])+x[2]*(y[0]-y[1]));
		printf("%d\n",a);
	}
	return 0;
}
