#include<bits/stdc++.h>
using namespace std;
int main(){
	string str;int age;
	vector<pair<string,int>>v;
	while(cin>>str>>age){
		v.push_back(make_pair(str,age));
	}
	sort(v.begin(),v.end(),[](const pair<string,int>&a,const pair<string,int>&b){
		if(a.second==b.second){
			return a.first<b.first;
		}	
		else{
			return a.second>b.second;
		}
	});
	for(auto x:v){
		cout<<x.first<<" "<<x.second<<endl;;
	}
}
