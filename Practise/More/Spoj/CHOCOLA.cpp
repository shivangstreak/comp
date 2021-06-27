#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
int M[1005],N[1005];
/*bool cmp(int &a,int &b){
	return a>b;
}*/
int main(){
	int sum1,sum2,m,n,t;scanf("%d",&t);
	while(t--){
		scanf("%d%d",&m,&n);
		m--;n--;
		sum1=0;sum2=0;
		for(int i=0;i<m;i++){
			scanf("%d",&M[i]);
			sum1+=M[i];
		}
		for(int i=0;i<n;i++){
			scanf("%d",&N[i]);
			sum2+=N[i];
		}
		sort(M,M+m,greater<int>());
		sort(N,N+n,greater<int>());
		/*for(int i=0;i<m;i++){
			cout<<M[i]<<" ";
		}
		cout<<endl;
		for(int i=0;i<n;i++){
			cout<<N[i]<<" ";
		}
		cout<<endl;*/	
		ll ans=sum1+sum2;
		int i=0,j=0;
		while(i<m && j<n){
			if(M[i]>=N[j]){
				ans+=sum2;
				sum1-=M[i];
				i++;
			}
			else{
				ans+=sum1;
				sum2-=N[j];
				j++;
			}
		}
		while(i<m){
			ans+=sum2;
			sum1-=M[i];
			i++;
		}
		while(j<n){
			ans+=sum1;
			sum2-=N[j];
			j++;
		}		
		printf("%lld\n",ans);
	}
	return 0;
}
