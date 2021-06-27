#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
int a[N];
ll ans;
struct node{
	ll sum,larger;
	node(){
		sum=larger=-1;
	}
}segTree[N*4];
void buildTree(int root,int start,int end){
	if(start==end){
	//	cout<<root<<" "<<a[start]<<endl;
		segTree[root].sum=a[start];
		segTree[root].larger=a[start];
		return;
	}
	int mid=(start+end)>>1;
	buildTree(root*2+1,start,mid);
	buildTree(root*2+2,mid+1,end);
	segTree[root].larger=max(segTree[2*root+1].larger,segTree[2*root+2].larger);
	segTree[root].sum=max(segTree[2*root+1].sum,max(segTree[2*root+2].sum,segTree[2*root+1].larger+segTree[2*root+2].larger));
}
void update(int root,int start,int end,int indx,int val){
	if(start==end){
		a[indx]=val;
		segTree[root].sum=a[start];
		segTree[root].larger=a[start];
		return;
	}
	int mid=(start+end)>>1;
	if(start<=indx && indx<=mid){
		update(2*root+1,start,mid,indx,val);
	}
	else{
		update(2*root+2,mid+1,end,indx,val);
	}
	segTree[root].larger=max(segTree[2*root+1].larger,segTree[2*root+2].larger);
	segTree[root].sum=max(segTree[2*root+1].sum,max(segTree[2*root+2].sum,segTree[2*root+1].larger+segTree[2*root+2].larger));
}
node query(int root,int start,int end,int l,int r){
	/*if(r<start || l>end){
		return -1;
	}*/
	if(l<=start && end<=r){
		return segTree[root];
	}
	int mid=(start+end)>>1;
	node ans1,ans2;
	if(l<=mid)
		ans1=query(2*root+1,start,mid,l,r);
	if(r>mid)
		ans2=query(2*root+2,mid+1,end,l,r);
	node temp;
	temp.larger=max(ans1.larger,ans2.larger);
	temp.sum=max(ans1.sum,max(ans2.sum,ans1.larger+ans2.larger));
	return temp;
}
int main(){
	int n;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	buildTree(0,0,n-1);
/*	cout<<"segTree\n";
	for(int i=0;i<=8;i++){
		cout<<i<<" sum is ";
		cout<<segTree[i].sum<<" large is "<<segTree[i].larger<<endl;
	}*/
//	cout<<"now query part\n";
	int q;scanf("%d",&q);
	while(q--){
		char ch;
		int x,y;
		cin>>ch;
		scanf("%d%d",&x,&y);
		//cout<<ch<<" "<<x<<" "<<y<<endl;
		x--;
		if(ch=='U'){
			//a[x]=y;
			update(0,0,n-1,x,y);
		}
		else{
			y--;
			//cout<<x<<" "<<y<<endl;
			printf("%lld\n",query(0,0,n-1,x,y).sum);
		}
	}
	return 0;
}
