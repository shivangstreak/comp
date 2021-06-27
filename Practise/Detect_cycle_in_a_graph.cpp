#include<bits/stdc++.h> // Undirected Graph!!!
using namespace std;
vector<int>g[100];
bool vis[100];
bool isCyclicUtil(int v,int parent){
	vis[v]=true;
	for(auto x:g[v]){
		if(vis[x]==false){
			if(isCyclicUtil(x,v))
				return true;
		}
		else if(x!=parent){  // If adjacent vertex is visited and is not its parent!! then graph has a cycle!!
			return true;
		}
	}
	return false;
}
bool iscyclic(){
		for(int i=1;i<=4;i++){
			if(vis[i]==false){
				 if (isCyclicUtil(i,-1))
               				 return true;
			}
		}
		return false;
}
int main(){
		memset(vis,false,sizeof(vis));
		g[1].push_back(2);
		g[2].push_back(1);
		g[2].push_back(3);
		g[3].push_back(2);
		g[3].push_back(4);
		g[4].push_back(3);
		//g[1].push_back(4);
		//g[4].push_back(1);
		if(iscyclic()){
			cout<<"It has a cycle!!\n";
		}
		else{
			cout<<"It does't have a cycle\n";
		}
		return 0;
} 
            
