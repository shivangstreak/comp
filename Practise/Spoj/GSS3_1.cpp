#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=5*1e4+5;
#define NEG -1000000
int arr[N];
struct node{
	ll sum,left,right,result;
	void merge(node &a,node &b){
		sum=a.sum+b.sum;
		left=max(a.left,a.sum+b.left);
		right=max(b.right,b.sum+a.right);
		result=max(a.right+b.left,max(a.result,b.result));
	}
	node(){
		sum=left=right=result=NEG;
	}
	void init(int val){
		sum=left=right=result=val;
	}	
}segTree[4*N];
void buildTree(int pos,int start,int end){
	if(start>end){
		return;
	}
	if(start==end){
		segTree[pos].init(arr[start]);
		return;
	}
	int mid=start+((end-start)>>1);
	buildTree(2*pos+1,start,mid);
	buildTree(2*pos+2,mid+1,end);
	segTree[pos].merge(segTree[2*pos+1],segTree[2*pos+2]);
}
void update(int pos,int start,int end,int indx,int val){
	if(start>end){
		return;
	}
	if(start==end){
		segTree[pos].init(val);
		return;
	}
	int mid=start+((end-start)>>1);
	if(start<=indx && indx<=mid)
		update(2*pos+1,start,mid,indx,val);
	else	
		update(2*pos+2,mid+1,end,indx,val);
	segTree[pos].merge(segTree[2*pos+1],segTree[2*pos+2]);	
}
node query(int pos,int start,int end,int l,int r){
	if(l<=start && r>=end){
		return segTree[pos];
	}
	int mid=start+((end-start)>>1);
	node l_node=node(),r_node=node();
	if(l<=mid){
		l_node=query(2*pos+1,start,mid,l,r);
	}
	if(r>mid){
		r_node=query(2*pos+2,mid+1,end,l,r);
	}
	node temp=node();
	temp.merge(l_node,r_node);
	return temp;
}
int main(){
	int d,q,l,r,n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	buildTree(0,0,n-1);
	scanf("%d",&q);
	while(q--){
		scanf("%d%d%d",&d,&l,&r);
		if(d==1){
			l--;r--;
			printf("%lld\n",query(0,0,n-1,l,r).result);
		}
		else{
			l--;
			update(0,0,n-1,l,r);
		}
	}
	return 0;
}
