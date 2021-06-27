#include<bits/stdc++.h>
using namespace std;
int main(){
	set<int>s;
	int n;scanf("%d",&n);
	vector<int>v;
	for(int i=0;i<n;i++){
		int d;scanf("%d",&d);
		v.push_back(d);
		int m;scanf("%d",&m);
		while(m--){
			scanf("%d",&d);
			s.insert(d);
		}
	}
	for(auto x:v){
		if(s.find(x)!=s.end())
			s.erase(s.find(x));
	}
	cout<<s.size()<<"\n";
	return 0;
}
