#include<bits/stdc++.h> // Find out the connected Components
using namespace std;
map<int,vector<int>>graph;
map<int,bool>vis;
set<int>Set;
void dfs(int i){
	stack<int>s;
	s.push(i);
	while(!s.empty()){
		int t=s.top();s.pop();
		if(vis[t]==true){
			continue;
		}
		vis[t]=true;
		int y=graph[t].size();
		for(int j=0;j<y;j++){
			s.push(graph[t][j]);
		}	
	}
}
int main(){
	int n,m;scanf("%d%d",&n,&m);	
	while(m--){
		int a,b;scanf("%d%d",&a,&b);
		graph[a].push_back(b);
		graph[b].push_back(a);
		Set.insert(a);
		Set.insert(b);
	}
	int c=0;
	vector<int>V(Set.begin(),Set.end());
	int Size=V.size();
	for(int i=0;i<Size;i++){
		if(vis[V[i]]==false){
			dfs(V[i]);
			c++;
		}	
	}
	cout<<c+n-Size<<"\n";	
	return 0;
}
