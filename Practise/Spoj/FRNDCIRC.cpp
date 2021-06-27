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
		h++;
		ll y=g[top].size();
		for(ll j=0;j<y;j++){
			s.push(g[top][j]);
		}
	}
}
int main(){
	int t;scanf("%d\n",&t);
	while(t--){
		g.clear();
		vis.clear();
		int n;scanf("%d\n",&n);
		ll c=1;
		map<string,ll>m;
		while(n--){
			string str1,str2;cin>>str1>>str2;
			if(m[str1]==0){
				m[str1]=c;
				c++;
			}
			if(m[str2]==0){
				m[str2]=c;
				c++;
			}
			vis.clear();
			ll h=0,k=0;
			dfs(m[str1],h);
			dfs(m[str2],k);
			if(h==1 || k==1){
				cout<<h+k<<"\n";
			}
			else{
				cout<<h*k<<"\n";
			}
			g[m[str1]].push_back(m[str2]);
			g[m[str2]].push_back(m[str1]);
		}
	}
	return 0;
}
