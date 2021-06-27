#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
int x[N],y[N];
int x_1[N];
int n;
int main(){ 
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&x[i],&y[i]);
		x_1[x[i]]++;
	}
	for(int i=0;i<n;i++){
		printf("%d %d\n",n-1+x_1[y[i]],(n-1)-x_1[y[i]]);		
	}
	return 0;
}
