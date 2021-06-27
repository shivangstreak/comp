#include<bits/stdc++.h>
using namespace std;
int n;
char D[30][30];
int vis[30][30];
int X[]={1,1,1,-1,-1,-1,0,0};
int Y[]={1,0,-1,1,0,-1,-1,1};
bool chk_bound(int i,int j){
	if(i<n && j<n && vis[i][j]==false && D[i][j]=='1'){
		return true;
	}
	else{
		return false;
	}
}
void dfs(int i,int j,int c){
	vis[i][j]=c;
	for(int k=0;k<8;k++){
		if(chk_bound(i+X[k],j+Y[k])==true){
			dfs(i+X[k],j+Y[k],c);
		}
	}
}
int main(){
	int lol=0;
	while(cin>>n){
		lol++;
		memset(vis,0,sizeof(vis));
		for(int i=0;i<n;i++){
			scanf("%s",D[i]);
		}
		int sum=1;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				if(vis[i][j]==0 && D[i][j]=='1'){
					dfs(i,j,sum);
					sum++;
				}
			}
		}
		printf("Image number %d contains %d war eagles.\n",lol,sum-1);
	}
	return 0;
}
