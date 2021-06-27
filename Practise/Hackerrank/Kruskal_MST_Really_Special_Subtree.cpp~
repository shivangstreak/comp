#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=3005;
vector<pair<int,pair<int,int>>>v;
int cost[N][N];
int parent[N];
int size[N];
int size1;
ll sum=0;
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
	a=root(a);
	b=root(b);
	if(a==b){
		return;
	}
	else{
		if(size[a]>size[b]){
			swap(a,b);
		}
		parent[a]=b;
		size[b]+=size[a];
	}
}
void Krushal(){
	int a,b;
	size1=v.size();
	for(int i=0;i<size1;i++){
		a=v[i].second.first;
		b=v[i].second.second;
		if(root(a)!=root(b)){
			sum+=v[i].first;
			Union(a,b);
		}
	}	
}
int main(){
	int s,n,m,a,b,w;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cost[i][j]=-1;
		}
	}
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		parent[i]=i;
		size[i]=1;
	}
	while(m--){
		scanf("%d%d%d",&a,&b,&w);
		v.pb({w,{a,b}});
	}
	scanf("%d",&s);
	sort(v.begin(),v.end());
	Krushal();
	cout<<sum<<"\n";
	return 0;
}
