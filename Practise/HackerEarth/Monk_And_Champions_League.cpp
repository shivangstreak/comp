#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
int main(){
	priority_queue<int>q;
	int m,n;scanf("%d%d",&m,&n);
	for(int i=0;i<m;i++){
		int d;scanf("%d",&d);
		q.push(d);
	}
	ll sum=0;
	while(n--){
		int o=q.top();
		q.pop();
		sum+=o;
		o--;
		q.push(o);
	}
	cout<<sum<<"\n";
	return 0;
}
