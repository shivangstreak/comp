#include<bits/stdc++.h>
using namespace std;
int y,m,n,a,b;
struct node{
	int a,b;
}V[100];
bool vis[100];
void dfs(int a){
	vis[a]=true;
	int i;
	for(int i=0;i<y;i++){
		if( ((V[a].a>V[i].a && V[a].a<V[i].b) ||(V[a].b>V[i].a && V[a].b<V[i].b)) && vis[i]==false){
			dfs(i);
		}
	}
}
int main(){
	scanf("%d",&n);
	y=0;
	while(n--){
		scanf("%d%d%d",&m,&a,&b);
		if(m==1){
			V[y].a=a;V[y].b=b;
			y++;
		}
		else{
			memset(vis,false,sizeof(vis));
			a-=1;b-=1;
			dfs(a);
			if(vis[b]==true){
				printf("YES\n");
			}
			else{
				printf("NO\n");
			}
		}
	}
	return 0;
}

