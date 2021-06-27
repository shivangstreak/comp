#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+5;
int a[N];
ll Count[N];
int main(){
	int n,d;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&d);
		Count[d]++;
	}
	for(int i=2;i<N;i++){
		Count[i]=max(Count[i-1],Count[i-2]+Count[i]*i);
	}
	printf("%lld\n",Count[N-1]);
	return 0;
}
