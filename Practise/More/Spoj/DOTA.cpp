#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,m,d,temp;scanf("%d%d%d",&n,&m,&d);
		priority_queue<int>q;
		for(int i=0;i<n;i++){
			scanf("%d",&temp);
			q.push(temp);
		}
		int flag=0;
		for(int i=0;i<m;i++){
			if(q.empty()==false){
				int top=q.top();
				q.pop();
				if(top>d){
					top-=d;
					q.push(top);			
				}
				else{
					flag=1;break;
				}
			}
		}
		if(flag==1){
			printf("NO\n");
		}
		else{
			printf("YES\n");
		}
	}
	return 0;
}
