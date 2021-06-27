#include<bits/stdc++.h>
using namespace std;
int main(){
	vector<int>q;
	q.push_back(1);
	q.push_back(2);
	q.push_back(3);
	q.push_back(4);
	q.erase(q.begin());
	for(auto x:q){
		cout<<x<<" ";
	}
	return 0;
}
