#include<bits/stdc++.h>
using namespace std;
int r,c;
char D[110][110];
bool vis[110][110];
int X[]={1,-1,0,0};
int Y[]={0,0,1,-1};
int flag1;
bool checkBound(int i,int j){
	if(i>=0 && i<r && j>=0 && j<c && D[i][j]!='*' && vis[i][j]==false){
		return true;
	}
	else{
		return false;
	}
}
void bfs(int i,int j){
	queue<pair<pair<int,int>,int>>q;
	q.push(make_pair(make_pair(i,j),0));
	vis[i][j]=true;
	while(q.empty()==false){
		pair<pair<int,int>,int> top=q.front();
		q.pop();
		if(D[top.first.first][top.first.second]=='#'){
			printf("%d\n",top.second);
			flag1=1;
			return;
		}
		for(int k=0;k<4;k++){
			if(checkBound(top.first.first+X[k],top.first.second+Y[k])==true){
				vis[top.first.first+X[k]][top.first.second+Y[k]]=true;
				q.push(make_pair(make_pair(top.first.first+X[k],top.first.second+Y[k]),top.second+1));
			}	
		}
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		memset(vis,false,sizeof(vis));
		int start_i,start_j;
		scanf("%d%d",&r,&c);
		int flag=0;
		for(int i=0;i<r;i++){
			scanf("%s",D[i]);
			for(int j=0;j<c && flag!=1;j++){
				if(D[i][j]=='$'){
					flag=1;
					start_i=i;start_j=j;
				}
			}
		}
		flag1=0;
		bfs(start_i,start_j);
		if(flag1==0){
			printf("-1\n");
		}
	}
	return 0;
}
