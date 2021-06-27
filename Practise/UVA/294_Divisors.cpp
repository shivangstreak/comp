#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int no_of_divisor(int n){
	int pro=1;
	for(int i=2;i*i<=n;i=((i==2)?3:i+2)){
		int Count=0;
		while(n%i==0){
			Count++;
			n/=i;
		}
		pro*=Count+1;
	}
	if(n!=1){
		pro*=1+1;
	}
	return pro;
}
int main(){
	int l,r,t,d,mx,index;scanf("%d",&t);
	while(t--){
		mx=-1;
		scanf("%d %d",&l,&r);
		for(int i=l;i<=r;i++){
			int y=no_of_divisor(i);
			if(mx<y){
				mx=y;
				index=i;
			}
		}
		printf("Between %d and %d, %d has a maximum of %d divisors.\n",l,r,index,mx);
	}
	return 0;
}
