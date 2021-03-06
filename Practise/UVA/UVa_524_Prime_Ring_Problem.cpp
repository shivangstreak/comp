#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
int vis[25];
int circle[25];
int arr[25];
int n;
bool isPrime(int k){
	for(int i=2;i<=sqrt(k);i++){
		if(k%i==0){
			return false;
		}
	}
	return true;
}
void f(int m){
	if(m==n-1){
		if(isPrime(circle[n]+circle[m])==true){
              	  	for(int i = 0; i < n; i++){
                   	        printf(i == n - 1? "%d" : "%d ", circle[i]);
	                }
	                printf("\n");
		}
		return;
	}
	for(int i=2;i<=n;i++){
		if(vis[i]==0 && isPrime(i+circle[m])){
			vis[i]=1;
			circle[m+1]=i;
			f(m+1);
			vis[i]=0;
		}
	}
}
int main(){
	int k=1;
	for(int i=0;i<25;i++){
		arr[i]=i;
	}
	while(scanf("%d",&n)==1){
		memset(vis,0,sizeof(vis));
		if(k>1)
			printf("\n");
		circle[0]=1;
		circle[n]=1;
		printf("Case %d:\n",k++);
		f(0);
	}
	return 0;
}
