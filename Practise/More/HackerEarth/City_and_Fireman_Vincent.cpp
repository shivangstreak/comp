#include<bits/stdc++.h>
using namespace std;
#define MOD 1000000007
int root(int i,map<int,int> &parent){
	if(parent[i]!=i){
		parent[i]=root(parent[i],parent);
	}
	return parent[i];
}
void Union(int a,int b,map<int,int> &parent,map<int,int> &size){
	int x=root(a,parent);
	int y=root(b,parent);
	if(size[x]>size[y]){
		swap(x,y);
	}
	parent[x]=y;
	size[y]+=size[x];
}
int main(){
	int n;scanf("%d",&n);
	map<int,int>parent;
	map<int,int>size;
	map<int,int>risk;
	for(int i=1;i<=n;i++){  //Initializing
		parent[i]=i;
		size[i]=1;
		int k;scanf("%d",&k);
		risk[i]=k;
	}
	int q;scanf("%d",&q);
	while(q--){
		int a,b;scanf("%d%d",&a,&b);
		Union(a,b,parent,size);
	}
	map< int,vector<int> >sets;
	for(int i=1;i<=n;i++){
		sets[root(i,parent)].push_back(risk[i]);
	}
	int c=1;
	for(auto x:sets){
		int min=*min_element(x.second.begin(),x.second.end());
		int count=0;
		for(auto y:x.second){
			if(y==min){
				count++;
			}
		}
		c=((c%MOD)*(count%MOD))%MOD;
	}
	printf("%d\n",c);
	return 0;
}
