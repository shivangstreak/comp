#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		priority_queue<int,vector<int>,greater<int>>q;
		vector< pair<int,int> >v;
		int n;scanf("%d",&n);
		int a[n];
		for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=0;i<n;i++){
			int d;scanf("%d",&d);
			v.push_back(make_pair(a[i],a[i]+d));
		}
		sort(v.begin(),v.end());
		int c=1;
		q.push(v[0].second);
		for(int i=1;i<v.size();i++){
			int s=v[i].first;
			if(s>=q.top()){
				q.pop();
				q.push(v[i].second);
			}
			else{
				c++;
				q.push(v[i].second);
			}
		}
		printf("%d\n",c);
	}
	return 0;
}
