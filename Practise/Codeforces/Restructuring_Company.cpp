#include<bits/stdc++.h>
using namespace std;
int parent[200005];
int size[200005];
void initialize(int n){
	for(int i=1;i<=n;i++){
		parent[i]=i;
		size[i]=1;
	}
}
int root(int i){
	if(parent[i]!=i){
		parent[i]=root(parent[i]);
	}
	return parent[i];
}
void Union(int a,int b){
	int x=root(a);
	int y=root(b);
	if(x==y)
		return;
	if(size[x]>size[y]){
		swap(x,y);
	}
	parent[x]=y;
	size[y]+=size[x];
}
int main(){
	int n,q;scanf("%d%d",&n,&q);
	initialize(n);
	for(int i=0;i<q;i++){
		int c,a,b;scanf("%d%d%d",&c,&a,&b);
		if(c==1)
			Union(a,b);
		else if(c==2){
			set<int>s;
			for(int i=a;i<=b;i++)
				s.insert(root(i));
			vector<int>v(s.begin(),s.end());
			int y=v.size();
			for(int i=0;i<y-1;i++){
				Union(v[i],v[i+1]);
			}	
		}	
		else{
			int x=root(a);
			int y=root(b);
			if(x==y){
				printf("YES\n");
			}
			else{
				printf("NO\n");
			}
		}
	}
	return 0;
}
