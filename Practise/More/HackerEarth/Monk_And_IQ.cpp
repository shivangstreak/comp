#include<bits/stdc++.h>
using namespace std;
struct node{
	int index;
	int z;
	node(int i,int z1){
		index=i;
		z=z1;
	}
};
bool operator<(const node &x,const node &y){
	if (x.z!=y.z) return x.z>y.z; //For minHeap...
	else return x.index>y.index; //For minHeap...
}
int main(){
	int c,p,n;scanf("%d%d%d",&c,&p,&n);
	priority_queue<node>q;
	int a[c+1];
	memset(a,0,sizeof(a));
	vector<int>sum[c+1];
	int i;
	for(i=1;i<=n;i++){
		a[i]++;
		int d;scanf("%d",&d);
		q.push(node(i,d));
		sum[i].push_back(d);
	}
	for(;i<=c;i++){
		q.push(node(i,0));
		sum[i].push_back(0);
	}
	vector<int>P;
	for(i=0;i<p;i++){
		int d;scanf("%d",&d);
		P.push_back(d);
	}
	for(int j=0;j<p;j++){
		node s=q.top();q.pop();
		cout<<s.index<<" ";
		a[s.index]++;
		sum[s.index].push_back(P[j]);
		int s1=0;
		for(auto x:sum[s.index]){
			s1+=x;
		}
		sum[s.index].erase(sum[s.index].begin());
		q.push(node(s.index,s1*a[s.index]));
	}
	return 0;
}
