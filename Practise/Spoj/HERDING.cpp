#include<bits/stdc++.h>
using namespace std;
int r,c;
char D[1005][1005];
pair<int,int>parent[1005][1005];
int size[1005][1005];
set<pair<int,int>>Set;
bool vis[1005][1005];
pair<int,int> root(int a,int b){
	if (parent[a][b] != make_pair(a,b))
		parent[a][b]=root(parent[a][b].first,parent[a][b].second);
	return parent[a][b];
}
void Union(int a,int b,int c,int d){
	pair<int,int>root1=root(a,b);
	pair<int,int>root2=root(c,d);
	if (root1==root2)
		return;
	parent[root1.first][root1.second]=make_pair(root2.first,root2.second);
}
int main(){
	scanf("%d%d",&r,&c);
	for(int i=0;i<r;i++){
		scanf("%s",D[i]);
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			parent[i][j]=make_pair(i,j);
			size[i][j]=1;
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			if(vis[i][j]==false){
				vis[i][j]==true;
				if(D[i][j]=='N'){
					if(i-1>=0){
						Union(i-1,j,i,j);
					}
				}
				else if(D[i][j]=='S'){
					if(i+1<r){
						Union(i+1,j,i,j);
					}
				}
				else if(D[i][j]=='E'){
					if(j+1<c){
						Union(i,j+1,i,j);
					}
				}
				else{
					if(j-1>=0){
						Union(i,j-1,i,j);
					}			
				}					
			}
		}
	}
	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			Set.insert(root(i,j));
		}		
	}	
	cout<<Set.size()<<endl;
	return 0;
}
