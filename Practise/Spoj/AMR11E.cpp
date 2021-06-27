#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
const int N=1e4+1;
int Count[N];
int Mapped[1005];
bool prime[1006];
int main(){
	int n,t;scanf("%d",&t);
	prime[0]=true;
	prime[1]=true;
	for(int i=2;i<1006;i++){
		if(prime[i]==false){
			for(int j=i*i;j<1006;j+=i){
				prime[j]=true;
			}
		}
	}
	for(int i=2;i<=1005;i++){
		if(prime[i]==false){
			for(int j=i<<1;j<N;j+=i){
				Count[j]++;
			}		
		}
	}
	int i=1,j=30;
	//cout<<"Ready Bitchessss!!\n";
	while(j<N && i<1006){
		if(Count[j]>=3){
			Mapped[i]=j;
			i++;
		}
		j++;
	}
	//cout<<"Now\n";
	while(t--){
		scanf("%d",&n);
		printf("%d\n",Mapped[n]);
	}
	return 0;
}
