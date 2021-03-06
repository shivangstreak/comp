#include<bits/stdc++.h>
using namespace std;
char s[30005];
struct node{
	int no_of_unmatched_open,no_of_unmatched_closed;
}segTree[30005*4];
void buildTree(int root,int start,int end){
	if(start==end){
		if(s[start]=='('){
			segTree[root].no_of_unmatched_open=1;
			segTree[root].no_of_unmatched_closed=0;		
		}
		else{
			segTree[root].no_of_unmatched_open=0;
			segTree[root].no_of_unmatched_closed=1;			
		}		
		return;
	}
	else{
		int mid=(start+end)/2;
		buildTree(2*root+1,start,mid);
		buildTree(2*root+2,mid+1,end);
		int matched=min(segTree[2*root+1].no_of_unmatched_open,segTree[2*root+2].no_of_unmatched_closed);
	segTree[root].no_of_unmatched_open=segTree[2*root+1].no_of_unmatched_open+segTree[2*root+2].no_of_unmatched_open-matched;
	segTree[root].no_of_unmatched_closed=segTree[2*root+1].no_of_unmatched_closed+segTree[2*root+2].no_of_unmatched_closed-matched;
	}
}
void update(int root,int start,int end,int indx,char val){
	if(start==end){
		if(val=='('){
			segTree[root].no_of_unmatched_open=1;
			segTree[root].no_of_unmatched_closed=0;		
		
		}
		else{
			segTree[root].no_of_unmatched_open=0;
			segTree[root].no_of_unmatched_closed=1;	
		}
		return;	
	}
	int mid=(start+end)/2;
	if(start<=indx && indx<=mid){
		update(2*root+1,start,mid,indx,val);		
	}
	else{
		update(2*root+2,mid+1,end,indx,val);
	}
	int matched=min(segTree[2*root+1].no_of_unmatched_open,segTree[2*root+2].no_of_unmatched_closed);
	segTree[root].no_of_unmatched_open=segTree[2*root+1].no_of_unmatched_open+segTree[2*root+2].no_of_unmatched_open-matched;
	segTree[root].no_of_unmatched_closed=segTree[2*root+1].no_of_unmatched_closed+segTree[2*root+2].no_of_unmatched_closed-matched;
}
int main(){
	int n,q;
	int u;
	for(int k=1;scanf("%d",&n)==1;k++){
		scanf("%s",s);
		buildTree(0,0,n-1);
		scanf("%d",&q);
		printf("Test %d:\n",k);
		while(q--){
			scanf("%d",&u);
			u--;
			if(u==-1){
				if(segTree[0].no_of_unmatched_open==0 && segTree[0].no_of_unmatched_closed==0){
					printf("YES\n");
				}
				else{
					printf("NO\n");
				}
			}
			else{
				s[u]=(s[u]=='(')?')':'(';
				//cout<<"string is "<<s<<endl;
				//buildTree(0,0,n-1);
				update(0,0,n-1,u,s[u]);
			}				
		}
	}
	return 0;
}
