#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=100005;
int startTime[N],endTime[N],arr[N];
vector<int>g[N];
bool vis[N];
int Time=0;
struct node{
	int cnt,lazy;
	node(){
		cnt=0;
		lazy=0;
	}
}segTree[4*N];
void dfs_1(int x,int par){
        startTime[x]=++Time;
        int v,len=g[x].size();
        for(int i=0;i<len;i++){
                v=g[x][i];
                if(v!=par){
                        dfs_1(v,x);
                }
        }
        endTime[x]=Time;
}
/*void dfs(int x){
	startTime[x]=++Time;
	vis[x]=true;
	int v,len=g[x].size();
	for(int i=0;i<len;i++){
		v=g[x][i];
		if(vis[v]==false){
			dfs(v);
		}
	}
	endTime[x]=Time;
}*/
void buildTree(int pos,int start,int end){
	if(start>end){
		return;
	}
	if(start==end){
		segTree[pos].cnt=1;
		segTree[pos].lazy=0;
		return;
	}
	int mid=start+((end-start)>>1);
	buildTree(2*pos+1,start,mid);
	buildTree(2*pos+2,mid+1,end);
	segTree[pos].cnt=segTree[2*pos+1].cnt+segTree[2*pos+2].cnt;
}
void update(int pos,int start,int end,int l,int r,int type){
	if(start>end)
		return;	
	if(segTree[pos].lazy!=0){
		if(segTree[pos].lazy==1){
			segTree[pos].cnt=end-start+1;
		}
		else{
			segTree[pos].cnt=0;
		}
		if(start!=end){
			segTree[2*pos+1].lazy=segTree[pos].lazy;
			segTree[2*pos+2].lazy=segTree[pos].lazy;
		}
		segTree[pos].lazy=0;
	}
	if(start>r || l>end){
		return;
	}
	if(l<=start && end<=r){
		if(type==1){
			segTree[pos].cnt=end-start+1;
		}
		else{
			segTree[pos].cnt=0;
		}
		if(start!=end){
			segTree[2*pos+1].lazy=type;
			segTree[2*pos+2].lazy=type;
		}
		return;
	}
	int mid=start+((end-start)>>1);
	update(2*pos+1,start,mid,l,r,type);
	update(2*pos+2,mid+1,end,l,r,type);
	segTree[pos].cnt=segTree[2*pos+1].cnt+segTree[2*pos+2].cnt;
}
int query(int pos,int start,int end,int l,int r){
	if(start>end || start>r || l>end){
		return 0;
	}
	if(segTree[pos].lazy!=0){
		if(segTree[pos].lazy==1){
			segTree[pos].cnt=end-start+1;
		}
		else{
			segTree[pos].cnt=0;
		}
		if(start!=end){
			segTree[2*pos+1].lazy=segTree[pos].lazy;
			segTree[2*pos+2].lazy=segTree[pos].lazy;
		}
		segTree[pos].lazy=0;
	}
	if(l<=start && end<=r){
		return segTree[pos].cnt;
	}
	int mid=start+((end-start)>>1);
	return	query(2*pos+1,start,mid,l,r)+query(2*pos+2,mid+1,end,l,r);
}
int main(){
	int s,d,q,n;scanf("%d",&n);
	int root;
	for(int i=1;i<=n;i++){
		scanf("%d",&d);
		if(d==0){
			root=i;
			continue;
		}
		g[d].pb(i);
	}
	//dfs(root);
	dfs_1(root,0);
	buildTree(0,1,n);
	scanf("%d",&q);
	while(q--){
		scanf("%d%d",&d,&s);
		if(d==3){
			printf("%d\n",query(0,1,n,startTime[s]+1,endTime[s]));
		}
		else{
			update(0,1,n,startTime[s]+1,endTime[s],d);
		}
	}
	return 0;
}
