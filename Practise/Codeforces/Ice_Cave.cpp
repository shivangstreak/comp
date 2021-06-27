#include<bits/stdc++.h>
using namespace std;
const int mx=505;
char D[mx][mx];
bool vis[mx][mx];
int X[]={0,0,1,-1};
int Y[]={1,-1,0,0};
int R,C;
bool checkBound(int i,int j){
	if(i>=0 && i<R && j>=0 && j<C){
		return true;
	}
	else{
		return false;
	}
}
int flag2=0;
bool dfs(int i,int j,int t1,int t2){
	vis[i][j]==true;
	if(flag2==1 && i==t1 && j==t2){
		return true;
	}
	else{
		flag2=1;
		for(int k=0;k<4;k++){
			if(checkBound(i+X[k],j+Y[k])){
				if(vis[i+X[k]][j+Y[k]]==false && (D[i+X[k]][j+Y[k]]!='X' || (i+X[k]==t1 && j+Y[k]==t2))){
					vis[i+X[k]][j+Y[k]]=true;
					bool d=dfs(i+X[k],j+Y[k],t1,t2);
					if(d==true){
						return true;
					}
				}
			}
		}
	}
	vis[i][j]=false;
	return false;
}
bool dfs2(int i,int j,int t1,int t2){
	vis[i][j]==true;
	if(i==t1 && j==t2){
		return true;
	}
	else{
		for(int k=0;k<4;k++){
			if(checkBound(i+X[k],j+Y[k])){
				if(vis[i+X[k]][j+Y[k]]==false && D[i+X[k]][j+Y[k]]!='X'){
					vis[i+X[k]][j+Y[k]]=true;
					bool d=dfs(i+X[k],j+Y[k],t1,t2);
					if(d==true){
						return true;
					}
				}
			}
		}
	}
	vis[i][j]=false;
	return false;	
}
//int flag=0;
/*bool dfs3(int i,int j,int t1,int t2){
	vis[i][j]==true;
	if(flag==1 && i==t1 && j==t2){
		return true;
	}
	else{
		flag=1;
		for(int k=0;k<4;k++){
			if(checkBound(i+X[k],j+Y[k])){
				if((vis[i+X[k]][j+Y[k]]==false || (i+X[k]==t1 && j+Y[k]==t2)) && D[i+X[k]][j+Y[k]]!='X'){
					vis[i+X[k]][j+Y[k]]=true;
					bool d=dfs(i+X[k],j+Y[k],t1,t2);
					if(d==true){
						return true;
					}
				}
			}
		}
	}
	vis[i][j]=false;
	return false;	
}*/
int main(){
	scanf("%d%d",&R,&C);
	memset(vis,false,sizeof(vis));
	for(int i=0;i<R;i++){
		scanf("%s",D[i]);
	}
	int or1,tr2,oc1,tc2;
	scanf("%d%d%d%d",&or1,&oc1,&tr2,&tc2);
	or1--;tr2--;oc1--;tc2--;
	if(D[tr2][tc2]=='X'){
		if(dfs(or1,oc1,tr2,tc2)){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	else{
		if(dfs2(or1,oc1,tr2,tc2)){
			int flag3=1;
			for(int y=0;y<4;y++){
				if(vis[tr2+X[y]][tc2+Y[y]]==false && D[tr2+X[y]][tc2+Y[y]]!='X'){
					flag3=0;
					break;
				}
			}
			if(flag3==1){
				printf("NO\n");
			}
			else{
				printf("YES\n");	
			}
		}
		else{
			printf("NO\n");
		}
	}
	for(int i=0;i<R;i++){
		for(int j=0;j<C;j++){
			cout<<vis[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
