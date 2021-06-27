#include<bits/stdc++.h>
using namespace std;
#define S(n) scanf("%d",&n);
int main(){
	int n,q;S(n);S(q);
	string str;cin>>str;
	while(q--){
		int a,b,k;S(a);S(b);S(k);
		string str1="",str2="",str3="";
		for(int i=0;i<a-1;i++){
			str1+=str[i];
		}
		for(int i=a-1;i<b;i++){
			str2+=str[i];
		}
		for(int i=b;i<n;i++){
			str3+=str[i];
		}
		sort(str2.begin(),str2.end());
		if(k==0){
			reverse(str2.begin(),str2.end());
		}
		str=str1+str2+str3;
	}
	cout<<str<<"\n";
	return 0;
}
