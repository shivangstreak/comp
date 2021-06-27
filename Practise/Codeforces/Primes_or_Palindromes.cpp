#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
const int mx = 2e6;
bool a[mx];
int pal(int i){
	int rem=0;
	while(i!=0){
		rem=rem*10+i%10;
		i/=10;
	}
	return rem;
}
int A=0,B=0,ans;
int main(){
	int p,q;scanf("%d%d",&p,&q);
	memset(a,true,sizeof(a));
	/*for(int i=0;i<mx;i++){
		a[i]=true;
	}*/
	a[0]=false;a[1]=false;
	for(int i=1;i<mx;i++){
		if(a[i]==true){
			A++;  // Incerase the count of number of Prime numbers...
			for(ll j=i*i;j<mx;j+=i){
				a[j]=false;
			}		
		}
		if(pal(i)==i) B++;
		if(A*q<=B*p)ans=i;
	}
	cout<<ans<<"\n";
	return 0;
}
