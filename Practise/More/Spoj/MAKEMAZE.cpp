#include<bits/stdc++.h>
using namespace std;
char D[25][25];
bool vis[25][25];
int r,c;
int X[]={0,0,1,-1};
int Y[]={1,-1,0,0};
int end_i,end_j;
bool checkBound(int i,int j){
	if(i>=0 && i<r && j>=0 && j<c && D[i][j]!='#'){
		return true;
	}
	else{
		return false;
	}
}
int flag1=0;
void dfs(int i,int j){
	vis[i][j]=true;
	if(D[i][j]=='t'){
		flag1=1;
		return;
	}
	for(int k=0;k<4;k++){
		if(checkBound(i+X[k],j+Y[k])){
			if(vis[i+X[k]][j+Y[k]]==false){
				dfs(i+X[k],j+Y[k]);
				if(flag1==1)
					return;
			}
		}
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		flag1=0;
		memset(vis,false,sizeof(vis));
		scanf("%d%d",&r,&c);
		for(int i=0;i<r;i++){
			scanf("%s",D[i]);
		}
		int e=0;
		int flag=0;
		for(int j=0;j<c;j++){
			if(D[0][j]=='.'){
				e++;
				if(e>2){
					flag=1;
					break;
				}
			}
		}
		if(flag==1){
			printf("invalid\n");
			continue;
		}
		for(int j=0;j<c && r-1!=0;j++){
			if(D[r-1][j]=='.'){
				e++;
				if(e>2){
					flag=1;
					break;
				}
			}
		}
		if(flag==1){
			printf("invalid\n");
			continue;
		}
		for(int i=1;i<r-1;i++){
			if(D[i][0]=='.'){
				e++;	
			}
			if(e>2){
				flag=1;
				break;
			}
		}
		if(flag==1){
			printf("invalid\n");
			continue;
		}
		for(int i=1;i<r-1 && c-1!=0;i++){
			if(D[i][c-1]=='.'){
				e++;	
			}
			if(e>2){
				flag=1;
				break;
			}
		}
		if(flag==1){
			printf("invalid\n");
			continue;
		}
		if(e<2){
			printf("invalid\n");
			continue;			
		}
		flag=0;
		int start_i,start_j,end_i,end_j;
		for(int i=0;i<c;i++){
			if(D[0][i]=='.'){
				if(flag==0){
					start_i=0;
					start_j=i;
					D[0][i]='s';
					flag=1;
				}
				else{
					D[0][i]='t';
					end_i=0;
					end_j=i;
				}
			}
		}
		for(int j=0;j<c;j++){
			if(D[r-1][j]=='.'){
				if(flag==0){
					D[r-1][j]='s';
					start_i=r-1;
					start_j=j;
					flag=1;
				}
				else{
					D[r-1][j]='t';
					end_i=r-1;
					end_j=j;
				}
			}
		}
		for(int i=1;i<r-1;i++){
			if(D[i][0]=='.'){
				if(flag==0){
					D[i][0]='s';
					start_i=i;
					start_j=0;
					flag=1;
				}	
				else{
					D[i][0]='t';
					end_i=i;
					end_j=0;
				}
			}
		}
		for(int i=1;i<r-1;i++){
			if(D[i][c-1]=='.'){
				if(flag==0){
					D[i][c-1]='s';
					start_i=i;
					start_j=c-1;
					flag=1;
				}
				else{
					D[i][c-1]='t';
					end_i=i;
					end_j=c-1;
				}	
			}
		}
		/*for(int i=0;i<r;i++){
			for(int j=0;j<c;j++){
				cout<<D[i][j]<<" ";
			}
			printf("\n");
		}
		cout<<"End index\n";
		cout<<end_i<<" "<<end_j<<endl;
		cout<<"Start index\n";
		cout<<start_i<<" "<<start_j<<endl;*/
		dfs(start_i,start_j);
		if(flag1==0){
			printf("invalid\n");
		}
		else{
			printf("valid\n");
		}
	}
	return 0;
}
