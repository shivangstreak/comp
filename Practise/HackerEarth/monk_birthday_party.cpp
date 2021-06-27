#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;cin>>t;
	while(t--){
		set<string>s;
		int n;cin>>n;
		while(n--){
			string str;cin>>str;
			s.insert(str);
		}
		vector<string>v(s.begin(),s.end());
	sort(v.begin(),v.end());
	for(auto x:v){
		cout<<x<<endl;
	}
	}
}
