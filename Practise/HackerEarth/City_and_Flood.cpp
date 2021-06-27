#include<bits/stdc++.h>
using namespace std;
void initialize(int n,map<int, int> &parent,map<int, int> &size){
	for(int i=1;i<=n;i++){
		parent[i]=i;
		size[i]=1;
	}
}
int root(int i,map<int, int> &parent){
	if(parent[i]!=i){
		parent[i]=root(parent[i],parent);
	}
	return parent[i];
}
void Union(int a,int b,map<int, int> &parent,map<int, int> &size){
	int x=root(a,parent);
	int y=root(b,parent);
	if(size[x]>size[y]){
		swap(x,y);
	}
	parent[x]=y;
	size[y]+=size[x];
}
int main(){
	int n,k;scanf("%d%d",&n,&k);
	map<int,int>parent,size;
	initialize(n,parent,size);
	for(int i=0;i<k;i++){
		int a,b;scanf("%d%d",&a,&b);
		Union(a,b,parent,size);
	}
	vector<int>v;
	for(int i=1;i<=n;i++){
		v.push_back(root(i,parent));
	}
	set<int>s1(v.begin(),v.end());
	printf("%d\n",s1.size());
	return 0;
}
