#include<bits/stdc++.h>
using namespace std;
int u,n;
char s[30005];
struct node{
	int sum,minVal;	
}segTree[30005*4];
void update(int root,int start,int end){
	if(u!=0 && (u<start || u>end)){
		return;
	}
	if(start==end){
		if(s[start]=='('){
			segTree[root].sum=1;
			segTree[root].minVal=1;	
		}
		else{
			segTree[root].sum=-1;
			segTree[root].minVal=-1;				
		}
	}
	else{
		int mid=(start+end)/2;
		update(root*2+1,start,mid);
		update(root*2+2,mid+1,end);
		segTree[root].sum=segTree[root*2+1].sum+segTree[root*2+2].sum;
		segTree[root].minVal=min(segTree[root*2+1].minVal,segTree[root*2+1].sum+segTree[root*2+2].minVal);
	}
}
int main(){
	for(int k=1;scanf("%d",&n)==1 && n>0;k++){
		scanf("%s",s);
		printf("Test %d:\n",k);
		u=0;
		update(0,0,n-1);
		int q;scanf("%d",&q);
		while(q--){
			scanf("%d",&u);
			u--;
			if(u==-1){
				if(segTree[0].sum==0 && segTree[0].minVal==0){
					printf("YES\n");
				}
				else{
					printf("NO\n");
				}
			}
			else{
				if(s[u]=='('){
					s[u]=')';
				}
				else{
					s[u]='(';
				}
				update(0,0,n-1);
			}
		}
	}
	return 0;
}
