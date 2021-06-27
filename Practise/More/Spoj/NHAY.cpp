#include<bits/stdc++.h>
using namespace std;
int n;string str1,str2;
int main(){
	int len;	
	while(cin>>n>>str1>>str2){
		len=str2.size();
		if(n>len){
			cout<<"\n";
			continue;
		}
		else{
			int j=0;
			int k=str2.find(str1,j);
			while(k!=string::npos){
				cout<<k<<"\n";
				j=k+1;
				k=str2.find(str1,j);
			}
			cout<<"\n";
		}
	}
	return 0;
}
