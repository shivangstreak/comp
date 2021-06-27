#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
	int t;scanf("%d",&t);
	while(t--){
		priority_queue<ll>p;
		int q1[40005],q2[40005];
		int w,h,n1,n;scanf("%d%d%d",&w,&h,&n);
		int i=0;
		n1=n;
		while(n1--){
			int a,b;scanf("%d%d",&a,&b);
			q1[i]=a;
			q2[i]=b;
			i++;
		}
		sort(q1,q1+n);
		sort(q2,q2+n);
		set<int>s1,s2;
		for(int i=0;i<n;i++){
			if(i==0){
				s1.insert(q1[i]-1);
			}
			else{
				s1.insert(q1[i]-q1[i-1]-1);
			}
		}
		if(q1[n-1]!=w){
			s1.insert(w-q1[n-1]);
		}
		for(int i=0;i<n;i++){
			if(i==0){
				s2.insert(q2[i]-1);
			}
			else{
				s2.insert(q2[i]-q2[i-1]-1);
			}
		}	
		if(q2[n-1]!=h){
			s2.insert(h-q2[n-1]);
		}		
		ll z;	
		for(auto x:s1){
			for(auto y:s2){
				z=x*y;
				p.push(z);
			}
		}
		printf("%lld\n",p.top());
	}
	return 0;
}
