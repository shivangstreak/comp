#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;scanf("%d",&n);
	vector<int>v,v1;
	int a[100005];
	memset(a,0,sizeof(a));
	for(int i=0;i<n;i++){
		int d;scanf("%d",&d);
		v.push_back(d);
		if(d>=1 && d<=n)
			a[d]++;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==0){
			v1.push_back(i);
		}
	}
	int j=0;
	for(int i=0;i<n;i++){
		if(v[i]>=1 && v[i]<=n && a[v[i]]>1){
			a[v[i]]--;
			v[i]=v1[j++];
		}
		else if(!(v[i]>=1 && v[i]<=n)){
			v[i]=v1[j++];
		}
	}
	for(auto x:v){
		printf("%d ",x);
	}
	printf("\n");
	return 0;
}
