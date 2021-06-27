#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e5+5;
int parent[N][18]; 
//Let parent[i][j] be 2^jth parent of node i. Initially we know parent[i][0] i.e. first parent of all the nodes.
int isnode[N],a[N];
int main(){
	int d,p,q,x,y,t;scanf("%d",&t);
	while(t--){
		for(int i=0;i<N;i++){
			for(int j=0;j<18;j++){
				parent[i][j]=0;
			}
		}
		for(int i=0;i<N;i++){
			isnode[i]=0;
		}
		scanf("%d",&p);
		for(int i=0;i<p;i++){
			scanf("%d%d",&x,&y);
			a[i]=x;
			isnode[x]=1;
			parent[x][0]=y;
		}
		for(int j=1;j<18;j++){
			for(int i=0;i<p;i++){
				parent[a[i]][j]=parent[parent[a[i]][j-1]][j-1];
			}
		}
		scanf("%d",&q);
		while(q--){
			scanf("%d",&d);
			if(d==0){
				scanf("%d%d",&y,&x);
				// X is added as a leaf node whose parent is y
				isnode[x]=1;
				parent[x][0]=y;
				int j=0;
				while(parent[x][j]!=0){
					parent[x][j+1]=parent[parent[x][j]][j];
					j++;
				}
				while(j<18){
					parent[x][j]=0;
					j++;
				}
			}
			else if(d==1){
				scanf("%d",&x);
				// remove leaf node x
				isnode[x]=0;
				for(int i=0;i<18;i++){
					parent[x][i]=0;
				}
			}
			else{
				scanf("%d%d",&x,&y);
				// tell the yth parent of x
				int j=0;
				while(y>0){
					if(y&1){
						x=parent[x][j];
					}
					y=y>>1;
					j++;
				}
				printf("%d\n",x);
			}
		}
	}
	return 0;
}
