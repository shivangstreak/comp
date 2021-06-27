#include<bits/stdc++.h>
using namespace std;
int chk(string str){
	int len=str.size();
	for(int i=0;i<len;i++){
		if(str[i]=='_'){
			return 1;
		}
		if((str[i]>='A' && str[i]<='Z')){
			return 0;
		}
	}
	return 1;
}
string convertToc(string str){
	int len=str.size();
	int i=0;
	string s="";
	while(i<len){
		if((str[i]>='A' && str[i]<='Z')){
			s+='_';
			s+=str[i]+32;
		}
		else{
			s+=str[i];
		}		
		i++;
	}
	return s;
}
string convertTojava(string str){
	int len=str.size();
	int i=0;
	string s="";
	while(i<len){
		if(str[i]=='_' && i+1<len){
			i++;
			s+=str[i]-32;
		}
		else{
			s+=str[i];
		}
		i++;
	}
	return s;
}
int main(){
	string str;
	while(cin>>str){
		int len=str.size();
		if(str[0]>='A' && str[0]<='Z' || str[0]=='_' || str[len-1]=='_'){
			printf("Error!\n");
			continue;
		}
		int flag=1,u=0,y=0;
		for(int i=0;i<len-1;i++){
			if(u==0 && (str[i]=='_' || str[i+1]=='_')){
				u=1;
			}
			if(y==0 && ((str[i]>='A' && str[i]<='Z') || (str[i+1]>='A' && str[i+1]<='Z')) ){
				y=1;
			}
			if(y&u==1){
				printf("Error!\n");
				flag=0;
				break;				
			}
			if(str[i]=='_' && str[i+1]=='_'){
				printf("Error!\n");
				flag=0;
				break;
			}
		}
		if(flag==0){
			continue;
		}
		int h=chk(str);
		if(h==1){
			cout<<convertTojava(str)<<"\n";
		}
		else{
			cout<<convertToc(str)<<"\n";
		}
	}
	return 0;
}
