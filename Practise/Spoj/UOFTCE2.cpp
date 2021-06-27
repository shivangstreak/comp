#include<bits/stdc++.h> // Using Bfs instead of dfs accepted but in dfs TLE...
using namespace std;
int r,c,a,b,ans,Count;
char D[110][110];
bool vis[110][110];
int X[]={0,0,1,-1};
int Y[]={-1,1,0,0};
priority_queue<int>q;
bool checkBound(int i,int j){
	if(i>=0 && i<r && j>=0 && j<c && D[i][j]!='#' && vis[i][j]==false){
		return true;
	}
	else{
		return false;
	}
}
void bfs(int i,int j){
	queue<pair<pair<int,int>,int>>q1;
	q1.push(make_pair(make_pair(i,j),0));
	vis[i][j]=true;
	while(q1.empty()==false){
		pair<pair<int,int>,int> top=q1.front();
		q1.pop();	
		if(D[top.first.first][top.first.second]=='S'){
			//cout<<top.first.first<<" "<<top.first.second<<endl;
			//cout<<"Level is "<<top.second<<endl;
			q.push(top.second);
		}
		for(int k=0;k<4;k++){
			if(checkBound(top.first.first+X[k],top.first.second+Y[k])==true){
				vis[top.first.first+X[k]][top.first.second+Y[k]]=true;	
				q1.push(make_pair(make_pair(top.first.first+X[k],top.first.second+Y[k]),top.second+1));
			}
		}
	}
}
int main(){
	int t,start_i,start_j;scanf("%d",&t);
	while(t--){
		while(q.empty()==false){
			q.pop();
		}
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
				}
			}
		}
		memset(vis,false,sizeof(vis));
		bfs(start_i,start_j);
		if(q.empty()==false){
			ans+=q.top();
			q.pop();
		}
		while(q.empty()==false){
			ans+=2*q.top();
			q.pop();
		}
		cout<<ans<<"\n";
	}
	return 0;
}
