#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		priority_queue<int>q;
		int n,m;scanf("%d%d",&n,&m);
		int a[10];
		int M;
		memset(a,0,sizeof(a));
		for(int i=0;i<n;i++){
			int d;scanf("%d",&d);
			if(i==m){
				M=d;
			}
			if(a[d]==0){
				q.push(d);
			}
			a[d]++;
		}
		int c=0;
		while(q.empty()==false){
			int s=q.top();
			if(s==M){
				if(a[s]>1)
					c+=a[s]-1;
				else
					c+=a[s];	
				break;
			}
			else{
				c+=a[s];
			}
			q.pop();
		}
		printf("%d\n",c);
	}
	return 0;
}
