#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a[100005];
struct node{
	int val,a,b;
	node(){}
	node(int v,int i,int j){
		val=v;a=i;b=j;
	}
};
bool operator<(const node &A,const node &B){
	if(A.b==B.b){
		return A.a<B.a;
	}
	return A.b<B.b;  
}
int main(){
	int d,n,k;scanf("%d%d",&n,&k);
	int sum=0;
	priority_queue<node>q;
	for(int i=0;i<n;i++){
		scanf("%d",&d);
		if(d>=100){
			sum+=10;
			continue;
		}
		q.push(node(d,d/10,d%10));
	}
	/*while(q.empty()==false){
		cout<<q.top().val<<" ";
		q.pop();
	}*/
	while(q.empty()==false && k!=0){
		node top=q.top();
		q.pop();
		int y=(top.a+1)*10;
		if(k>=(y-top.val)){
			k-=y-top.val;
			if(y!=100){
				q.push(node(y,top.a+1,0));
			}				
			else{
				sum+=10;
			}
		}
		else{
			sum+=top.a;
		}
	}
	while(q.empty()==false){
		sum+=q.top().a;
		q.pop();
	}
	printf("%d\n",sum);
	return 0;
}
