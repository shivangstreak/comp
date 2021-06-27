#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int lim=1e5+5;
int parent[lim],size[lim],Values[lim],box[lim];
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
	/*if(size[x]>size[y]){
		swap(x,y);
	}*/
	parent[x]=y;
	//size[y]+=size[x];
}
int main(){
	int n,q;scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		size[i]=1;
		parent[i]=i;
		Values[i]=i;
	}
	int l,r,a,b;
	while(q--){
		scanf("%d%d",&l,&r);
		a=Values[l];b=Values[r];
		Values[l]=0;
		if(b!=0){
			Union(a,b);
		}
		else{
			Values[r]=a;
		}
	}
	for(int i=1;i<=n;i++){
		box[Values[i]]=i;
	}
	for(int i=1;i<=n;i++){
		printf("%d ",box[root(i)]);
	}
	printf("\n");
	return 0;
}
