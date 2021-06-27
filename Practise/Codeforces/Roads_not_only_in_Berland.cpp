#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
pair<int,int>DEL[1005],NEW[1005];
int parent[1005],size[1005];
int root(int n){
	if(parent[n]!=n){
		parent[n]=root(parent[n]);
	}
	return parent[n];
}
void Union(int a,int b){
	a=root(a);
	b=root(b);
	if(a==b)
		return;
	else{
		if(size[a]>size[b]){
			swap(a,b);
		}
		size[b]+=size[a];
		parent[a]=b;
	}
}
int main(){
	int a,b,n;scanf("%d",&n);
	int k=0,l=0;
	for(int i=1;i<=n;i++){
		size[i]=1;
		parent[i]=i;
	}
	for(int i=0;i<n-1;i++){
		scanf("%d %d",&a,&b);
		if(root(a)==root(b)){
			DEL[k].first=a;
			DEL[k].second=b;
			k++;
		}
		else{
			Union(a,b);
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			if(i==j)
				continue;
			a=root(i);
			b=root(j);
			if(a==b){
				continue;
			}
			NEW[l].first=a;
			NEW[l].second=b;
			l++;
			Union(a,b);
		}		
	}
	printf("%d\n",l);
	for(int i=0;i<l;i++){
		printf("%d %d %d %d\n",DEL[i].first,DEL[i].second,NEW[i].first,NEW[i].second);
	}	
	return 0;
}
