#include<bits/stdc++.h>    // Range Minimum query!!!!
using namespace std;
#define ll long long
int n;
int  v1[100005];
int v[100005];
struct node{
	int val;
	node(){
		val=-99999;	
	}
	node(int v){
		val=v;
	}
	void merge(node a,node b){
		val=max(a.val,b.val);
	}
}tree[4*100005];
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
	scanf("%d",&n);
	int k=ceil(log(n)/log(2));
	int pos=1<<k;
	for(int i=0;i<n;i++){
		scanf("%d",&d);
		v[i]=d;
		tree[pos+i]=node(d);
		update(pos+i);
	}
	int l,r;
	for(int i=1;i<n;i++){
		v1[i-1]=range_query(1,1,pos,i+1,n).val;
	}
	for(int i=0;i<n-1;i++){
		if(v1[i]==v[i]){
			printf("1 ");
			continue;
		}
		else if(v1[i]<=v[i]){
			printf("0 ");
			continue;
		}
		printf("%d ",v1[i]+1-v[i]);
	}
	printf("0 \n");
	return 0;
}
