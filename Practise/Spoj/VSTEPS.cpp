#include<bits/stdc++.h>
using namespace std;
#define MOD 14062008
int main(){
	int n,k;scanf("%d%d",&n,&k);
	map<int,int>m;
	while(k--){
		int a;scanf("%d",&a);
		m[a]=1;
	}
	int f[n+2];
	f[0]=0;
	f[1]=1;
	if(m[2]!=1)
		f[2]=1;
	else{
		f[2]=0;
	}		
	for(int i=3;i<=n;i++){
		if(m[i]==1){
			f[i]=0;
		}
		else{
			f[i]=(f[i-1]%MOD+f[i-2]%MOD)%MOD;
		}
	}
	cout<<f[n]<<endl;
	return 0;
}
