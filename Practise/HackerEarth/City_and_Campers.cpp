#include<bits/stdc++.h>
using namespace std;
int root(int a,map<int,int> &parent){
	if(parent[a]!=a){
		parent[a]=root(parent[a],parent);
	}
	return parent[a];
}
void Union(int a,int b,map<int,int> &parent,map<int,int> &size){
	int x=root(a,parent);
	int y=root(b,parent);
	if(x==y)
		return;
	if(size[x]>size[y]){
		swap(x,y);
	}
	parent[x]=y;
	size[y]+=size[x];
}

bool find(int a,int b,map<int,int> &parent){
	if(root(a,parent)==root(b,parent)){
		return true;
	}
	else{
		return false;
	}
}
int main(){
	int n;scanf("%d",&n);
	map<int,int>parent,size;
	for(int i=1;i<=n;i++){
		parent[i]=i;
		size[i]=1;
	}
	int q;scanf("%d",&q);
	while(q--){
		int a,b;scanf("%d%d",&a,&b);
		Union(a,b,parent,size);
		map<int,int>m;
		for(int i=1;i<=n;i++){
			m[root(i,parent)]++;
		}
		if(m.size()==1){
			printf("0\n");
			continue;
		}
		vector<int>v;
		for(auto x:m){
			v.push_back(x.second);
		}
		int min=*min_element(v.begin(),v.end());
		int max=*max_element(v.begin(),v.end());
		printf("%d\n",max-min);
	}
	return 0;
}
