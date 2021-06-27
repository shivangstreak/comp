#include<bits/stdc++.h>
using namespace std;
#define ll unsigned long long
#define MOD 100000
int fib[1100005];
int Count[100005];
int main(){
	int t;scanf("%d",&t);
	fib[0]=0;fib[1]=1;fib[2]=1;
	for(int i=3;i<1100005;i++){
		fib[i]=(fib[i-1]%MOD+fib[i-2]%MOD)%MOD;
	}
	for(int k=1;k<=t;k++){
		int a,b;scanf("%d%d",&a,&b);
		priority_queue<int,vector<int>,greater<int>>q;
		int c=0;
		for(int i=a;i<=a+b;i++){
			q.push(fib[i-1]);
		}
		printf("Case %d: ",k);
		while(q.empty()==false && c<100){
			cout<<q.top()<<" ";
			q.pop();
			c++;
		}
		printf("\n");
	}
	return 0;
}
