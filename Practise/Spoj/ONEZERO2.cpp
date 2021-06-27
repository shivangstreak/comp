#include<bits/stdc++.h>
using namespace std;
int k,n;
int val[20005];
int parent[20005];
queue<int>q;
void bfs(){
	q.push(1);
	parent[1]=0;
	while(q.empty()==false){
		int state=q.front();
		q.pop();
		if(state==0){
			stack<int>s;
			while(parent[state]!=0){
				s.push(val[state]);
				state=parent[state];
			}
			s.push(1);
			while(s.empty()==false){
				printf("%d",s.top());
				s.pop();
			}
			printf("\n");
			break;
		}
		else{
			int temp=(state*10)%n;
			if(parent[temp]==-1){
				q.push(temp);
				parent[temp]=state;
				val[temp]=0;
			}
			temp=(state*10+1);
			temp%=n;	
			if(parent[temp]==-1){
				q.push(temp);
				parent[temp]=state;
				val[temp]=1;
			}
		}
	}
}
int main(){
	scanf("%d",&k);
	while(k--){
		while(q.empty()==false){
			q.pop();
		}
		memset(parent,-1,sizeof(parent));
		scanf("%d",&n);
		bfs();
	}
	return 0;
}
