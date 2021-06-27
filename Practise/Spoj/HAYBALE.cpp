#include<bits/stdc++.h>  // Range Update Point Query!!  Binary Indexed Tree
using namespace std;
int d[1000005];
int n;
void pointUpdate(int a,int val){
	while(a<=n){
		d[a]+=val;
		a=a+(a &(-a));
	}
}
void rangeUpdate(int a,int b,int val){
	pointUpdate(a,val);
	pointUpdate(b+1,-val);
}
int rangeQuery(int a,int ans){
	while(a>0){
		ans+=d[a];	
		a=a-(a & (-a));
	}
	return ans;
}
int main(){	
	int k;scanf("%d%d",&n,&k);
	int a,b;	
	while(k--){
		scanf("%d%d",&a,&b);
		rangeUpdate(a,b,1);
	}
	vector<int>v;
	for(int i=1;i<=n;i++){
		v.push_back(rangeQuery(i,0));
	}
	sort(v.begin(),v.end());
	cout<<v[n/2]<<"\n";
	return 0;
}
