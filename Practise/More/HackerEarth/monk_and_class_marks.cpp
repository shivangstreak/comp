#include<bits/stdc++.h>
using namespace std;
int comp(pair<string,int> a,pair<string,int> b){
	if(a.second > b.second){
		return 1;
	}
	else if(a.second == b.second){
		if(a.first <b.first)
			return 1;
		else
			return 0;
	}
	else{
		return 0;
	}
}
int main(){
	int n;cin>>n;
	vector<pair<string,int>>v;
	string str;
	int m;
	for(int i=0;i<n;i++){
		cin>>str>>m;
		v.push_back(make_pair(str,m));
	}
	sort(v.begin(),v.end(),comp);
	for(auto x:v){
		cout<<x.first<<" "<<x.second<<endl;
	}
	return 0;
}

