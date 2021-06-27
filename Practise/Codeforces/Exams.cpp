#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5005;
pair<int,int>A[N];
int main(){
	int n,l,r;scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&l,&r);
		A[i]={l,r};
	}
	sort(A,A+n);
	int mn=min(A[0].first,A[0].second);
	for(int i=1;i<n;i++){
		l=A[i].first;
		r=A[i].second;
		if(r>=mn && l>=mn){
			mn=min(r,l);
			continue;
		}
		else if(l>=mn && r<mn){
			mn=l;
		}
		else if(r>=mn && l<mn){
			mn=r;
		}
	}
	printf("%d\n",mn);
	return 0;
}
