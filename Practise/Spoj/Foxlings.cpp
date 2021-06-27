#include<bits/stdc++.h>
using namespace std;
map<int,int>parent,size;
multiset<pair<int,int>>Set;
void initialize(int n){
	for(int i=1;i<=n;i++){
		parent[i]=i;
		size[i]=1;
		Set.insert(make_pair(i,1));
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
	Set.erase(Set.find(make_pair(x,size[x])));
	Set.erase(Set.find(make_pair(y,size[y])));
	parent[x]=y;
	size[y]+=size[x];
	Set.insert(make_pair(y,size[y]));
}
int main(){
	int n,k;scanf("%d%d",&n,&k);
	initialize(n);
	for(int i=0;i<k;i++){
		int a,b;scanf("%d%d",&a,&b);
		Union(a,b);
	}
	printf("%d\n",Set.size());
	return 0;
}
