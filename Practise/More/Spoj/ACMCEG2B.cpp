#include<bits/stdc++.h>
using namespace std;
int main(){
	map<string,string>m;
	int n;scanf("%d",&n);
	string str;
	while(n--){
		int a,b;scanf("%d%d",&a,&b);
		str="";
		str+=a+'0';
		str+=b+'0';
		string str1;cin>>str1;
		m[str]=str1;
	}
	int t;scanf("%d",&t);
	while(t--){
		int a,b;scanf("%d%d",&a,&b);
		str="";
		str+=a+'0';
		str+=b+'0';
		cout<<m[str]<<"\n";
	}
	return 0;
}
