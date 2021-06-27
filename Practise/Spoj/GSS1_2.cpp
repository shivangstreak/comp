#include<bits/stdc++.h>  // Not Working !!!!!!!!!!!!!!!!
using namespace std;
int a[50005];
int st[200010];
void constructSegmentTree(int start,int end,int pos){
	if(start==end){
		st[pos]=a[start];
		return;
	}
	int mid=(start+end)/2;
	constructSegmentTree(start,mid,2*pos+1);
	constructSegmentTree(mid+1,end,2*pos+2);
	st[pos]=max(max( (st[2*pos+1]+st[2*pos+2]) ,st[2*pos+1]),st[2*pos+2]);
}
int query(int ss,int se,int qs,int qe,int pos){
	if (qs <= ss && qe >= se)
       		 return st[pos];
	if (se < qs || ss > qe)
       		return 0;

	 int mid = (ss+se)/2;
	return query(ss,mid,qs,qe,2*pos+1)+query(mid+1,se,qs,qe,2*pos+2);
}
int main(){	
	int l,r,n;scanf("%d",&n);
	for(int i=0;i<n;i++){	
		scanf("%d",&a[i]);
	}
	int m;scanf("%d",&m);
	constructSegmentTree(0,n-1,0);
 	/*int x = (int)(ceil(log2(n))); //Height of segment tree
   	 int max_size = 2*(int)pow(2, x) - 1; 
	for(int i=0;i<max_size;i++){
		cout<<st[i]<<" ";
	}	
	cout<<endl;*/
	while(m--){
		scanf("%d%d",&l,&r);
		cout<<query(0,n-1,l-1,r-1,0)<<"\n";
	}
	return 0;
}
