#include<bits/stdc++.h>
using namespace std;
int X[]={-2,-1,1,2,-2,-1,1,2};
int Y[]={1,2,2,1,-1,-2,-2,-1};
map<char,int>m;
int start_i,start_j,end_i,end_j;
bool vis[10][10];
int dist[100005];
int A[10][10];
bool checkBound(int i,int j){
	if(vis[i][j]==false && i>=1 && i<=8 && j>=1 && j<=8){
		return true;
	}
	else{
		return false;
	}
}
void bfs(){
	//cout<<"inside bfs "<<start_i<<" "<<start_j<<endl;
	queue<pair<pair<int,int>,int>>q;
	q.push(make_pair(make_pair(start_i,start_j),0));
	vis[start_i][start_j]=true;
	while(q.empty()==false){
		pair<pair<int,int>,int> top=q.front();
		q.pop();
		//cout<<"top "<<top.first.first<<" "<<top.first.second<<endl;
		//cout<<"top Level "<<top.second<<endl;
		if(top.first.first==end_i && top.first.second==end_j){
			int ans=top.second;
			printf("%d\n",ans);
			return;
		}
		else{
			for(int k=0;k<8;k++){
				if(checkBound(top.first.first+X[k],top.first.second+Y[k])==true){
					vis[top.first.first+X[k]][top.first.second+Y[k]]=true;
					q.push(make_pair(make_pair(top.first.first+X[k],top.first.second+Y[k]),top.second+1));
				}
			}
		}
	}
}
int main(){
	int t;scanf("%d",&t);
	m['a']=1;	
	m['b']=2;
	m['c']=3;
	m['d']=4;
	m['e']=5;
	m['f']=6;
	m['g']=7;
	m['h']=8;
	while(t--){
		memset(vis,false,sizeof(vis));
		string str1,str2;cin>>str1>>str2;
		//cout<<str1<<" "<<str2<<endl;	
		start_i=m[str1[0]];start_j=str1[1]-'0';
//		cout<<"start_i is "<<start_i<<"start_j is "<<start_j<<endl;
		end_i=m[str2[0]];end_j=str2[1]-'0';
//cout<<"end_i is "<<end_i<<"end_j is "<<end_j<<endl;
		bfs();
	}
	return 0;
}
