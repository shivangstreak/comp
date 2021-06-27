#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
map<string,string>mymap;
int main(){
	int n,m;scanf("%d%d",&n,&m);
	while(m--){
		string s1,s2;cin>>s1>>s2;
		mymap[s1]=s2;
	}
	for(int i=0;i<n;i++){
		string str;cin>>str;
		if(mymap[str].size()<str.size()){
			cout<<mymap[str]<<" ";
		}
		else{
			cout<<str<<" ";
		}
	}
	printf("\n");
	return 0;
}
