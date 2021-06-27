#include<bits/stdc++.h>
using namespace std;
int n,m,k;
int a[1100];
bool chk(int x,int y){
	int s=0;
	for(int i=0;i<n;i++){
		if(((1<<i)&x)!=((1<<i)&y)){
			s++;
			if(s>k){
				return false;
			}
		}
	}
	return true;
}
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=m+1;i++){
		scanf("%d",&a[i]);
	}
	int sum=0;
	for(int i=1;i<=m;i++){
		if(chk(a[m+1],a[i])==true){
			sum++;
		}
	}
	printf("%d\n",sum);
	return 0;
}
