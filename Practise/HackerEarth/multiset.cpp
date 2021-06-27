#include<bits/stdc++.h>
using namespace std;
struct cmp
{
	bool operator() (const pair<int, int>& a, const pair<int, int>& b)
	{
		return a.second > b.second;
	}
};
int main(){
	multiset<pair<int, int>, cmp> S;
	for (int i = 1; i <=5; i++){
		S.insert(make_pair(i, i+6));
	}
	for(auto x:S){
		cout<<x.first<<" "<<x.second<<"\n";
	}
	return 0;
}
