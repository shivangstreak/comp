#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
string str;
int cnt;
map<string,int>mymap;
int Count(string str){
	int c=0;
	for(int i=0;i<12;i++){
		if(str[i]=='o'){
			c++;
		}
	}
	return c;
}
int f(string str){
	if(mymap[str]!=0){
		return mymap[str];
	}
	string str1=str;
	for(int i=0;i<12;i++){
		if(str[i]=='o' && i+1<12 && str[i+1]=='o' && i+2<12 && str[i+2]=='-'){
			str[i]='-';str[i+1]='-';
			str[i+2]='o';
			mymap[str]=f(str);
			str=str1;
		}
		if(i-1>=0 && str[i-1]=='-' && str[i]=='o' && i+1<12 && str[i+1]=='o'){
			str[i-1]='o';
			str[i]='-';
			str[i+1]='-';
			mymap[str]=f(str);
			str=str1;
		}
	}
	int d=Count(str);
	if(d<cnt)
		cnt=d;
	return cnt;	
}
int main(){
	faster;
	int t;cin>>t;
	while(t--){
		cnt=100;
		mymap.clear();
		cin>>str;
		printf("%d\n",f(str));
	}
	return 0;
}
