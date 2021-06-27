#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	int b[100005];
	while(t--){
		int n;scanf("%d",&n);
		memset(b,0,sizeof(b));
		int c=0;
		for(int i=0;i<n;i++){
			int d;scanf("%d",&d);
			if(b[d]==0){
				c++;
				b[d]=1;
			}
		}
		printf("%d\n",c);
	}
	return 0;
}
