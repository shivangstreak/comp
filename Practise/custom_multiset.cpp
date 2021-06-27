#include<bits/stdc++.h>
using namespace std;
struct cmp{
	bool operator() (const pair<int, int>& a, const pair<int, int>& b){
		return a.second < b.second;
	}
};
int main(){
	multiset<pair<int,int>,cmp>set;
	set.insert({5,2});
	set.insert({1,3});
	set.insert({56,-1});
	for(auto x:set){
		cout<<x.first<<" "<<x.second<<endl;
	}
	return 0;
}
