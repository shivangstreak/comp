#include<bits/stdc++.h>
using namespace std;
bool chk(string a,string b){
	string t=b.substr(0,a.size());
	if(t==a){
		return true;
	}
	else{
		return false;
	}
}
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n;scanf("%d",&n);
		vector<string>str;
		for(int i=0;i<n;i++){
			string a;cin>>a;
			str.push_back(a);
		}
		sort(str.begin(),str.end());
		for(auto x:str){
			cout<<x<<endl;
		}
	/*	int f=1;
		for(int i=0;i<n-1;i++){
			if(chk(str[i],str[i+1])){
				printf("NO\n");
				f=0;
				break;
			}
		}
		if(f==1){
			printf("YES\n");
		}*/
	}
	return 0;
}
