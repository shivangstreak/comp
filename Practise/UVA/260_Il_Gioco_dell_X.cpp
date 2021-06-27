#include<bits/stdc++.h>
using namespace std;
int n,flag,flag1;
char D[250][250];
bool vis[250][250];
int X[]={-1,-1,0,0,1,1};
int Y[]={-1,0,-1,1,0,1};
bool chk_bound(int i,int j){
	if(flag==1){
		if(i<n && j<n && D[i][j]=='b' && vis[i][j]==false){
			return true;
		}
		else{
			return false;
		}
	}
	else{
		if(i<n && j<n && D[i][j]=='w' && vis[i][j]==false){
			return true;
		}
		else{
			return false;
		}	
	}
}
void dfs(int i,int j){
	vis[i][j]=true;
	for(int k=0;k<6;k++){
		if(chk_bound(i+X[k],j+Y[k])==true){
			if(flag==1 && i+X[k]==n-1){
				flag1=1;
				return;	
			}
			if(flag==0 && j+Y[k]==n-1){
				flag1=1;
				return;	
			}
			dfs(i+X[k],j+Y[k]);
		}
	}
}
int main(){
	int lol=0;
	while(true){
		lol++;
		scanf("%d",&n);
		if(n==0)
			break;
		memset(vis,false,sizeof(vis));
		for(int i=0;i<n;i++){
			scanf("%s",D[i]);
		}
		printf("%d ",lol);
		flag1=0;
		for(int i=0;i<n;i++){
			if(D[0][i]=='b'){
				flag=1;
				dfs(0,i);
				if(flag1==1){
					cout<<"B\n";
					break;
				}			
			}				
		}
		if(flag1==0){
			for(int i=0;i<n;i++){
				if(D[i][0]=='w'){
					flag=0;
					dfs(i,0);
					if(flag1==1){
						cout<<"W\n";
						break;
					}
				}
			}	
		}
	}
	return 0;
}
