#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
const int mx = 2e6;
int a[mx];
int pal(int i){
	int rem=0;
	while(i!=0){
		rem=rem*10+i%10;
		i/=10;
	}
	return rem;
}
int chk(int i){
	if(pal(i)==i){
		return 1;
	}
	else{
		return 0;
	}
}
int A=0,B=0,ans;
int main(){
	int p,q;scanf("%d%d",&p,&q);
	memset(a,1,sizeof(a));
	a[0]=0;a[1]=0;
	for(int i=1;i<mx;i++){
		if(a[i]==1){
			for(int j=2;j*i<mx;j++){
				a[j*i]=0;
			}		
		}
	}
	for(int i=1;i<mx;i++){
		 A+=a[i];
         B+=chk(i);
        if (B*p>=q*A) ans=i;
	}
	cout<<ans<<"\n";
	return 0;
}
