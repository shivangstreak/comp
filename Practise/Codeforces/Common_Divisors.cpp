#include<bits/stdc++.h>
using namespace std;
int const N=1e5+5;
#define ll long long
string s1,s2;
bool f(string s,int i){
	string temp=s.substr(0,i);
	int len=s.length();
	for(int j=0;j<len;j++){
		if(s1[j%i]!=s[j]){
			return false;
		}
	}
	return true;
}
int main(){
	char str1[N],str2[N];
	scanf("%s%s",str1,str2);
	s1=(string)str1;s2=(string)str2;
	int len1=strlen(str1),len2=strlen(str2);
	ll ans=0;
	for(int i=1;i<=len1;i++){
		if((len2%i==0 && len1%i==0 && f(s1,i) && f(s2,i))==true){
			ans++;
		}
	}
	cout<<ans<<"\n";
	return 0;
}
