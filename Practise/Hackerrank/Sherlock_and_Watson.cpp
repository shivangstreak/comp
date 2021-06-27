#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k,q;scanf("%d%d%d",&n,&k,&q);
	int a[n];
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	k=k%n;
	map<int,int>m;
	for(int i=0;i<n;i++){
		m[(i+k)%n]=a[i];
	}
	while(q--){
		int x;scanf("%d",&x);
		printf("%d\n",m[x]);
	}
	return 0;
}
