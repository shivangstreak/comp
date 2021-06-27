#include<bits/stdc++.h>
using namespace std;
map<int,int>m;
int r,c;
int Count;
int D[260][260];
bool vis[260][260];
int X[]={0,0,1,-1};
int Y[]={1,-1,0,0};
bool checkBound(int i,int j){
	if(i>=0 && i<r && j>=0 && j<c && vis[i][j]==false && D[i][j]==1){
		return true;
	}
	else{
		return false;
	}
}
void dfs(int i,int j){
	vis[i][j]=true;
	Count++;
	for(int k=0;k<4;k++){
		if(checkBound(i+X[k],j+Y[k])==true){	
			dfs(i+X[k],j+Y[k]);
		}
	}
}
int main(){
	while(true){
		scanf("%d%d\n",&r,&c);
		m.clear();
		if(r==0 && c==0){
			break;	
		}
		memset(vis,false,sizeof(vis));
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				scanf("%d",&D[i][j]);
			}
		}
		int y=0;
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				if(vis[i][j]==false && D[i][j]==1){
					Count=0;
					y++;
					dfs(i,j);
					m[Count]++;
				}
			}
		}
		printf("%d\n",y);
		for(auto x:m){
			printf("%d %d\n",x.first,x.second);
		}
	}
	return 0;
}
