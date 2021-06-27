#include<bits/stdc++.h>    // Range Minimum query!!!!
using namespace std;
int n;
struct node{
	int val;
	node(){
		val=INT_MAX;	
	}
	node(int v){
		val=v;
	}
	void merge(node a,node b){
		val=min(a.val,b.val);
	}
}tree[100];
void update(int pos){
	pos>>=1;
	while(pos!=0){
		tree[pos].merge(tree[2*pos],tree[2*pos+1]);
		pos>>=1;
	}
}
node range_query(int root,int left_most ,int right_most,int l,int r){
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
	int d;
	cin>>n;
	int k=ceil(log(n)/log(2));
	int pos=1<<k;
	for(int i=0;i<n;i++){
		cin>>d;
		tree[pos+i]=node(d);
		update(pos+i);
	}
	for(int i=1;i<8;i++){
		cout<<tree[i].val<<" ";
	}
	cout<<endl;
	int m;cin>>m;
	int l,r;
	while(m--){
		cin>>l>>r;
		cout<<range_query(1,1,pos,l,r).val<<"\n";
	}
	return 0;
}
