#include<bits/stdc++.h>
using namespace std;
char D[260][260];
int n,m,k,v;
bool vis[260][260];
int X[]={0,0,1,-1};
int Y[]={1,-1,0,0};
bool cheackBound(int i,int j){
	if(i>=0 && i<n && j>=0 && j<m && D[i][j]!='#'){
		return true;
	}
	else{
		return false;
	}
}
void dfs(int i,int j){
	vis[i][j]=true;
	if(D[i][j]=='v'){
		v++;
	}
	if(D[i][j]=='k'){
		k++;
	}
	for(int k=0;k<4;k++){
		if(cheackBound(i+X[k],j+Y[k])){
			if(vis[i+X[k]][j+Y[k]]==false){				
				dfs(i+X[k],j+Y[k]);
			}
		}
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		scanf("%s",D[i]);
	}
	memset(vis,false,sizeof(vis));
	int sheeps=0,wolfs=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(vis[i][j]==false){
				k=0,v=0;
				dfs(i,j);
				if(k>v){
					sheeps+=k;
				}		
				else{
					wolfs+=v;
				}		
			}
		}
	}
	printf("%d %d\n",sheeps,wolfs);
	return 0;
}
