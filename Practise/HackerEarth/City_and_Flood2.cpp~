#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int>parent;
unordered_map<int,int>Rank;
int Find(int i){
	if(parent[i]==i)
		return i;
	else{
		return Find(parent[i]);
	}	
}
void Union(int i,int j){
	if(Rank[i]>Rank[j]){
		parent[j]=i;
	}
	else if(Rank[i]<Rank[j]){
		parent[i]=j;
	}
	else{
		parent[i]=j;
		Rank[j]++;
	}
}
int main(){
	int n;scanf("%d",&n);
	int k;scanf("%d",&k);
	vector<int>v;
	for(int i=1;i<=n;i++){
		parent[i]=i;
		Rank[i]=0;
	}
	while(k--){
		int i,j;
		scanf("%d%d",&i,&j);
		Union(i,j);
	}
	for(int i=1;i<=n;i++){
		v.push_back(Find(i));
	}
	set<int>s1(v.begin(),v.end());
	cout<<s1.size()<<"\n";
	return 0;
}
