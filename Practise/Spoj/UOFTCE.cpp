#include<bits/stdc++.h>
using namespace std;
int r,c,a,b,ans,Count;
char D[110][110];
bool vis[110][110];
int X[]={0,0,1,-1};
int Y[]={-1,1,0,0};
bool checkBound(int i,int j){
	if(i>=0 && i<r && j>=0 && j<c && D[i][j]!='#' && vis[i][j]==false){
		return true;
	}
	else{
		return false;
	}
}
void dfs(int i,int j,int C){
	vis[i][j]=true;
	C++;	
	if(D[i][j]=='T'){
		Count=C;
		return;
	}
	for(int k=0;k<4;k++){
		if(checkBound(i+X[k],j+Y[k])==true){
			dfs(i+X[k],j+Y[k],C);		
		}
	}
}
int main(){
	int t,start_i,start_j;scanf("%d",&t);
	while(t--){
		vector<pair<int,int>>v;
		ans=0;
		scanf("%d%d",&r,&c);
		for(int i=0;i<r;i++){
			scanf("%s",D[i]);
			for(int j=0;j<c;j++){
				if(D[i][j]=='C'){
					start_i=i;start_j=j;
				}
				else if(D[i][j]=='S'){
					ans+=60;
					v.push_back(make_pair(i,j));
				}
			}
		}
		priority_queue<int>q;
		for(auto x:v){
			a=x.first;
			b=x.second;
			D[a][b]='T';
			int C=-1;
			memset(vis,false,sizeof(vis));
			dfs(start_i,start_j,C);
			q.push(Count);
			D[a][b]='S';
		}
		ans+=q.top();
		q.pop();
		while(q.empty()==false){
			ans+=2*q.top();
			q.pop();
		}
		cout<<ans<<"\n";
	}
	return 0;
}
