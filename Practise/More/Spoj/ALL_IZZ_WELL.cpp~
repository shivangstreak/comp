#include<bits/stdc++.h>
using namespace std;
const int mx=105;
char M[mx][mx];
int r,c;
char Pattern[11]={'A', 'L', 'L', 'I', 'Z', 'Z', 'W', 'E', 'L', 'L'};
bool vis[mx][mx];
int X[]={-1,0,1,-1,1,-1,0,1};
int Y[]={1,1,1,0,0,-1,-1,-1};
bool cheackBound(int i,int j){
	if(i>=0 && i<r && j>=0 && j<c){
		return true;
	}
	else{
		return false;
	}
}
string dfs(int i,int j,int p){
	vis[i][j]=true;
	if(p==9){
		return "YES";
	}
	string s;
	for(int k=0;k<8;k++){
		if(cheackBound(i+X[k],j+Y[k])){
				if(vis[i+X[k]][j+Y[k]]==false && M[i+X[k]][j+Y[k]]==Pattern[p+1]){
					vis[i+X[k]][j+Y[k]]==true;
					s=dfs(i+X[k],j+Y[k],p+1);
					if(s=="YES"){
						return s;
					}
				}	
		}
	}
	vis[i][j]=false;
	return "NO";
}
int main(){
	int t,flag;scanf("%d",&t);
	while(t--){
		scanf("%d%d",&r,&c);
		memset(vis,false,sizeof(vis));
		for(int i=0;i<r;i++){
			scanf("%s",M[i]);
		}
		flag=0;
		for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				if(M[i][j]=='A' && dfs(i,j,0)=="YES"){
					flag=1;
					break;
				}
			}
			if(flag==1){
				break;
			}
		}
		if(flag==1){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}
