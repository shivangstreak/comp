#include<bits/stdc++.h>
using namespace std;
const int mx=50;
vector<int>g[mx];
bool vis[mx];
vector<int>Final[48];
vector<int>vec3;
vector<int>vec2;
vector<int>vec1;
int j;
void dfs(int i,int &c,int j){
	vis[i]=true;
	//cout<<i<<" "; 
	Final[j].push_back(i);
	for(auto x:g[i]){
		if(vis[x]==false){
			c++;
			dfs(x,c,j);
		}
	}
}
int main(){
	int n,m,a,b;
	j=0;
	cin>>n>>m;	
	while(m--){
		cin>>a>>b;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	int flag=0;
	for(int i=1;i<=n;i++){
		if(vis[i]==false){
			//cout<<i<<" numbers \n";
			int c=1;
			dfs(i,c,j);
			if(c>3){
				printf("-1\n");
				flag=1;			
				break;
			}
			else if(c==3){
				vec3.push_back(j);
			}		
			else if(c==2){
				vec2.push_back(j);
			}
			else if(c==1){
				vec1.push_back(j);
			}
			j++;
		}
	}
	if(flag==0){
		int len2=vec2.size();
		int len1=vec1.size();
		if(len2>len1){
				printf("-1\n");
				return 0;	
		}
		for(auto x:vec3){
			for(auto y:Final[x]){
				cout<<y<<" ";
			}
			cout<<"\n";
		}
		if(len2==len1){
			for(int i=0;i<len2;i++){
				for(auto x:Final[vec2[i]]){
					cout<<x<<" ";
				}
				cout<<Final[vec1[i]][0]<<"\n";
			}
		}
		else{
			int i;
			for(i=0;i<len2;i++){
				for(auto x:Final[vec2[i]]){
					cout<<x<<" ";
				}
				cout<<Final[vec1[i]][0]<<"\n";
			}
			int y=len1-len2;
			int o=0;
			for(;i<len1;i++){
				cout<<Final[vec1[i]][0]<<" ";
				o++;
				if(o==3){
					printf("\n");
					o=0;	
				}
			}
		}
	}
	return 0;
}
