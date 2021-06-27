#include<bits/stdc++.h>
using namespace std;
int main(){
	int a[100002];
	int Q;scanf("%d",&Q);
	priority_queue<int>q;
	priority_queue< int,vector<int>,greater<int> >q1;
	memset(a,0,sizeof(a));
	for(int i=0;i<Q;i++){
		int n;scanf("%d",&n);
		if(n==1){
			int h;scanf("%d",&h);
			a[h]++;
			q.push(h);
			q1.push(h);
		}
		if(n==2){
			int h;scanf("%d",&h);
			if(a[h]!=0){
				a[h]--;
			}
			else{
				printf("-1");
			}
		}
		if(n==3){
			while(q.size() && a[q.top()]==0){
				q.pop();
			}
			if(q.size()!=0){
				printf("%d\n",q.top());
			}
			else{
				printf("-1\n");
			}
		}
		if(n==4){
			while(q1.size() && a[q1.top()]==0){
				q1.pop();
			}
			if(q1.size()!=0){
				printf("%d\n",q1.top());
			}
			else{
				printf("-1\n");
			}
		}
	}
	return 0;
}
