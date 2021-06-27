#include<bits/stdc++.h>
using namespace std;
const int mx=105;
char D[mx][mx];
bool vis[mx][mx];
int n,m;
int X[]={-1,0,1,0};
int Y[]={0,1,0,-1};
int ans,ron;
bool checkBound(int i,int j){
	if(i>=0 && i<n && j>=0 && j<m){
		return true;
	}
	else{
		return false;
	}
}
int flag;
void dfs(int i,int j,int s){
	vis[i][j]=true;
	if(D[i][j]=='*'){
		ans=s;
		flag=1;
		return;
	}
	for(int k=0;k<4;k++){
		if(checkBound(i+X[k],j+Y[k])){
			if(vis[i+X[k]][j+Y[k]]==false && D[i+X[k]][j+Y[k]]!='X'){
				vis[i+X[k]][j+Y[k]]=true;
				int count=0;
				for(int z=0;z<4;z++){
					if(checkBound(i+X[k]+X[z],j+Y[k]+Y[z])){
						if(vis[i+X[k]+X[z]][j+Y[k]+Y[z]]==false && D[i+X[k]+X[z]][j+Y[k]+Y[z]]!='X'){
							count++;
						}
					}
				}
				cout<<i+X[k]<<" "<<j+Y[k]<<" "<<D[i+X[k]][j+Y[k]]<<" "<<count<<endl;
				if(count>1 && D[i+X[k]][j+Y[k]]!='*'){
					dfs(i+X[k],j+Y[k],s+1);	
				}
				else{
					dfs(i+X[k],j+Y[k],s);
				}	
				if(flag==1){
					return;
				}
			}
		}		
	}
	vis[i][j]=false;
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		flag=0;
		int q,w,y,u;
		memset(vis,false,sizeof(vis));
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++){
			scanf("%s",D[i]);
			for(int j=0;j<m;j++){
				if(D[i][j]=='M'){
					q=i;w=j;	
				}
			}
		}
		scanf("%d",&ron);
		int s=0;
	//	cout<<q<<" "<<w<<endl;
		int c=0;
		for(int k=0;k<4;k++){
			if(checkBound(q+X[k],w+Y[k])){
				if(D[q+X[k]][w+Y[k]]!='X'){
					c++;	
				}
			}
		}
		if(c>1){
			c=1;
		}
		else{
			c=0;
		}
		dfs(q,w,s);
		cout<<"c "<<c<<" ans "<<ans<<"\n";
		if(ron==ans+c){
			printf("Impressed\n");
		}
		else{
			printf("Oops!\n");
		}
	}
	return 0;
}
