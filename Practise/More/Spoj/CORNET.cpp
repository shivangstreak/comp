#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=20005;
int res[N],parent[N];
int root(int i){
	int temp;
	if(i!=parent[i]){
		temp=parent[i];
		parent[i]=root(temp);
		res[i]+=res[temp];	
	}
	return parent[i];
}
void Union(int u,int v){
	if(root(u)==root(v)){
		return;
	}
	parent[u]=v;
	res[u]=abs(v-u)%1000;
}
int main(){
	int t,n,a,b;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			parent[i]=i;
			res[i]=0;
		}
		char ch[3];
		while(true){
			scanf("%s",ch);
			if(ch[0]=='O')
				break;
			else if(ch[0]=='E'){
				scanf("%d",&a);
				root(a);
				printf("%d\n",res[a]);
			}
			else{
				scanf("%d%d",&a,&b);
				Union(a,b);
			}	
		}
	}
	return 0;
}
