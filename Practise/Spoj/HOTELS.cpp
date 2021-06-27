#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll a[300000];
ll sum[300000];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++){
		cin>>a[i];
	}
	priority_queue<ll>q;
	sum[0]=0;
	for(int i=1;i<=n;i++){
		sum[i]=a[i-1]+sum[i-1];
	}
	int i=0,j=0;
	int flag=0;	
	ll temp=sum[j]-sum[i];
	while(i<=n && j<=n){
		if(temp<m){
			q.push(temp);
			temp=sum[++j]-sum[i];
		}
		else if(temp==m){		
			cout<<temp<<"\n";		
			flag=1;break;
		}
		else{
			temp=sum[j]-sum[++i];
		}
	}
	if(flag==0){
		cout<<q.top()<<"\n";
	}
	return 0;
}
