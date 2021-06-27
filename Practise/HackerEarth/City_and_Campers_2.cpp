#include<bits/stdc++.h>
using namespace std;
#define lim 1e5+1
#define maxn 1e5
#define maxq 1e5
struct cmp{
	bool operator() (const pair<int, int>& a, const pair<int, int>& b){
		return a.second < b.second;
	}
};
vector<int>parent(lim);
vector<int>size(lim);
multiset< pair<int,int>,cmp>s;
/*int root(int i){
        while(parent[i]!=i){
                parent[i]=parent[parent[i]];
                i=parent[i];
        }
        return i;
}*/
int root(int i){
	if(parent[i]!=i){
		parent[i]=root(parent[i]);
	}
	return parent[i];
}
void Union(int a,int b){
	int x=root(a);
	int y=root(b);
	if (x==y)
		return;
	if(size[x]>size[y]){
		swap(x,y);
	}
	s.erase(s.find(make_pair(x,size[x])));	
	s.erase(s.find(make_pair(y,size[y])));
	parent[x]=y;
	size[y]+=size[x];
	s.insert(make_pair(y,size[y]));
}
int main(){
	int n,q;
	scanf("%d%d", &n, &q);
	for(int i=1;i<=n;i++){
		parent[i]=i;
		size[i]=1;
		s.insert(make_pair(i,1));
	}
	while(q--){
		int a,b;scanf("%d%d",&a,&b);
		Union(a,b);
		int large = (*(s.rbegin())).second;
		int small = (*(s.begin())).second;
		printf("%d\n",large-small);
	}
	return 0;
}
