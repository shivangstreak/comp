#include <bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		string str;cin>>str;
		int c1=0,c2=0;
		int len=str.size();
		string str2="";
		string str3="";
		for(int i=0;i<len;i++){
			if(i%2==0){
				str2+='+';
			}
			else{
				str2+='-';
			}
		}
		for(int i=0;i<len;i++){
			if(i%2==0){
				str3+='-';
			}
			else{
				str3+='+';
			}
		}
		for(int i=0;i<len;i++){
			if(str[i]!=str2[i])
				c1++;
		}
		for(int i=0;i<len;i++){
			if(str[i]!=str3[i]){
				c2++;
			}
		}
		printf("%d\n",min(c1,c2));
	}
	return 0;
} 
