#include<bits/stdc++.h>
using namespace std;
vector<int>g[5005];
int d[5005][5005];
int a,b,n,e;
void bfs(){
	for(int i=1;i<=n;i++){
		queue<int>q;
		d[i][i]=0;
		q.push(i);
		while(q.empty()==false){
			int top=q.front();
			q.pop();
			for(auto x:g[top]){
				if(d[i][x]==-1){
					d[i][x]=d[i][top]+1;
					q.push(x);
				}
			}
		}
	}
}
int main(){
	memset(d,-1,sizeof(d));
	scanf("%d%d",&n,&e);
	int s[2],t[2],l[2];
	for(int k=0;k<e;k++){
		scanf("%d%d",&a,&b);
		g[a].push_back(b);
		g[b].push_back(a);
	}
	scanf("%d%d%d",&s[0],&t[0],&l[0]);
	scanf("%d%d%d",&s[1],&t[1],&l[1]);
	bfs();
	int ans=INT_MAX;
	for(int y=0;y<2;y++){
		swap(s[0],t[0]);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int v[]={ d[s[0]][i]+d[i][j]+d[j][t[0]],d[s[1]][i]+d[i][j]+d[j][t[1]] };		
				if(v[0]<=l[0] && v[1]<=l[1]){
					ans=min(ans,v[0]+v[1]-d[i][j]);			
				}
			}
		}
	}
	if(d[s[0]][t[0]]<=l[0] && d[s[1]][t[1]]<=l[1]){
		ans=min(ans,d[s[0]][t[0]]+d[s[1]][t[1]]);
	}
	if(ans>e){
		printf("-1\n");
	}
	else{
		ans=e-ans;
		printf("%d\n",ans);
	}
	return 0;
}
