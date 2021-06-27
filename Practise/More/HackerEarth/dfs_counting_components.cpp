#include<bits/stdc++.h>
using namespace std;
#define ll long long
map< ll,vector<ll> >g;
map<ll,bool>vis;
void dfs(ll i,ll &h){
	stack<ll>s;
	s.push(i);
	while(s.empty()==false){
		ll top=s.top();
		s.pop();
		if(vis[top]==true){
			continue;
		}
		vis[top]=true;
		cout<<top<<" ";
		h++;
		ll y=g[top].size();
		for(ll j=0;j<y;j++){
			s.push(g[top][j]);
		}
	}
	cout<<endl;
}
void addEdge(int a,int b){
		g[b].push_back(a);
			g[a].push_back(b);
}
int main(){
	addEdge(1,2);
	addEdge(3,2);
	addEdge(4,1);
	addEdge(6,7);
	ll h=0;
	dfs(2,h);	
	cout<<h<<endl;
		h=0;
	dfs(7,h);
	cout<<h<<endl;	
		h=0;
	dfs(8,h);
	cout<<h<<endl;	
	return 0;
}
