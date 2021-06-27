#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
const int N=1e6+5;
char s[N];
struct node{
	int len,open,closed;
	node(){
		len=open=closed=0;
	}
}segTree[N*4];
void buildTree(int root,int start,int end){
	if(start==end){
	//	cout<<root<<" "<<start<<" "<<s[start]<<endl;
		segTree[root].len=0;
		if(s[start]=='('){
			segTree[root].open=1;
			segTree[root].closed=0;	
		}
		else{
			segTree[root].open=0;
			segTree[root].closed=1;
		}
		return;
	}
	int mid=(start+end)>>1;
	buildTree(2*root+1,start,mid);
	buildTree(2*root+2,mid+1,end);
	int temp=min(segTree[2*root+1].open,segTree[2*root+2].closed);
	segTree[root].len=segTree[2*root+1].len+segTree[2*root+2].len+temp;
	segTree[root].open=segTree[2*root+1].open+segTree[2*root+2].open-temp;
	segTree[root].closed=segTree[2*root+1].closed+segTree[2*root+2].closed-temp;
}
node query(int root,int start,int end,int l,int r){
	if(l<=start && end<=r){
		return segTree[root];
	}
	int mid=(start+end)>>1;
	node ans1,ans2;
	if(l<=mid){
		ans1=query(2*root+1,start,mid,l,r);
	}
	if(r>mid){
		ans2=query(2*root+2,mid+1,end,l,r);		
	}
	node temp_node;
	int temp=min(ans1.open,ans2.closed);
	temp_node.len=ans1.len+ans2.len+temp;
	temp_node.open=ans1.open+ans2.open-temp;
	temp_node.closed=ans1.closed+ans2.closed-temp;
	return temp_node;
}
int main(){
	scanf("%s",s);
	int len=strlen(s);
	int a,b,m;scanf("%d",&m);
	buildTree(0,0,len-1);
	while(m--){
		scanf("%d%d",&a,&b);
		printf("%d\n",2*query(0,0,len-1,a-1,b-1).len);
	}
	return 0;
}
