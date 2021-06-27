#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		priority_queue<int>q;
		int n,m;scanf("%d%d",&n,&m);
		queue<int>q1,q2;
		for(int i=0;i<n;i++){
			int d;scanf("%d",&d);
			q1.push(i);q2.push(d);
			q.push(d);
		}
		int c=0;
		while(true){
			while(q2.front()!=q.top()){
				int temp=q2.front();
				q2.pop();
				q2.push(temp);
				temp=q1.front();
				q1.pop();
				q1.push(temp);
			}
			c++;
			if(q1.front()==m){
				printf("%d\n",c);
				break;
			}
			else{
				q1.pop();q2.pop();q.pop();
			}
		}
	}
	return 0;
}
