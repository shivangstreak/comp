#include<bits/stdc++.h>
using namespace std;
int r[55];
int a[55];
int mul[55];
int main(){
	int t;scanf("%d",&t);
	while(t--){
		priority_queue<int,vector<int>,greater<int>>q;
		int m,l;
		scanf("%d%d",&m,&l);
		for(int i=0;i<l;i++){
			scanf("%d",&r[i]);
			a[i]=r[i];
			q.push(r[i]);
			mul[i]=1;
		}
		int res;
		int c=0;
		while(true){
			res=q.top();
			q.pop();
			while(q.empty()==false && q.top()==res){
				q.pop();
			}
			for(int i=0;i<l;i++){
				if(a[i]==res){
					c++;
					mul[i]++;
					a[i]+=r[i]*mul[i];
					q.push(a[i]);
				}
			}
			if(c>=m)
				break;
		}
		cout<<res<<"\n";
	}
	return 0;
}
