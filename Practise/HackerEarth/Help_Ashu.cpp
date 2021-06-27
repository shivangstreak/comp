#include<bits/stdc++.h>
using namespace std;
struct node{
	int o,e;
	node(){o=e=0;}
	node(int v){
		if(v%2==0){
			e=1;
			o=0;
		}
		else{
			e=0;o=1;
		}
	}
	void merge(node &a,node &b){
		o=a.o+b.o;
		e=a.e+b.e;
	}
}tree[400050];
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
	int l_child=root*2,r_child=l_child+1,mid=(left_most+right_most)/2;
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
	int d,n;scanf("%d",&n);
	int k=ceil(log(n)/log(2));
	int pos=1<<k;
	for(int i=0;i<n;i++){
		scanf("%d",&d);
		tree[pos+i]=node(d);
		update(pos+i);;
	}
	int c,a,b;
	int m;scanf("%d",&m);
	while(m--){
		cin>>c>>a>>b;
		if(c==0){	
			int y=pos+a-1;
			tree[y]=node(b);	
			update(y);
		}
		else if(c==1){
			cout<<range_query(1,1,pos,a,b).e<<"\n";
		}
		else if(c==2){
			cout<<range_query(1,1,pos,a,b).o<<"\n";
		}
	}
	return 0;
}
