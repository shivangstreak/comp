#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define INT -1000000
struct node{
	ll sum,left,right,result;
	void merge(node &a,node &b){
		sum=a.sum+b.sum;
		left=max(a.left,a.sum+b.left);
		right=max(b.right,b.sum+a.right);
		result=max(a.right+b.left,max(a.result,b.result));
	}
	node(){
		sum=left=right=result=INT;
	}
	node(int val){
		sum=left=right=result=val;
	}
}tree[200020];
void update(int pos){
	pos>>=1;
	while(pos!=0){
		tree[pos].merge(tree[2*pos],tree[2*pos+1]);
		pos>>=1;
	}
}
node range_query(int root,int left_most,int right_most,int l,int r){
	if(l<=left_most && r>=right_most){
		return tree[root];
	}
	int l_child=root<<1,r_child=l_child+1,mid=(left_most+right_most)>>1;
	node l_node=node(),r_node=node();
	if(l<=mid){
		l_node=range_query(l_child,left_most,mid,l,r);
	}
	if(r>mid){
		r_node=range_query(r_child,mid+1,right_most,l,r);
	}
	node temp=node();
	temp.merge(l_node,r_node);
	return temp;
}
int main(){
	ll d;int n;scanf("%d",&n);
	int k=ceil(log(n)/log(2));
	int pos=1<<k;
	for(int i=0;i<n;i++){
		//scanf("%lld",&d);
		cin>>d;
		tree[pos+i]=node(d);
		update(pos+i);
	}
	int r,l,m;scanf("%d",&m);
	/*for(int i=1;i<=pos;i++){
		cout<<i<<" "<<tree[i].result<<"\n";
	}
	cout<<endl;*/
	while(m--){
		scanf("%d%d",&l,&r);
		cout<<range_query(1,1,pos,l,r).result<<"\n";
	}
	return 0;
}
