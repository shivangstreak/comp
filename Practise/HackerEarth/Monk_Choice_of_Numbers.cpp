#include<bits/stdc++.h>
using namespace std;
int number_so_set_bits(int n){
	int count=0;
	while(n!=0){
		n=n&(n-1);
		count++;
	}
	return count;
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		priority_queue<pair<int,int>>q;
		int n,k,a;
		scanf("%d%d",&n,&k);
		for(int i=0;i<n;i++){
			scanf("%d",&a);
			q.push(make_pair(number_so_set_bits(a),a));
		}
		int sum=0;
		while(k!=0 && q.empty()==false){
			sum+=q.top().first;
			q.pop();
			k--;
		}
		cout<<sum<<"\n";
	}
	return 0;
}
