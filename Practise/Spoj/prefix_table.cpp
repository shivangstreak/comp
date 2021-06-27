#include<bits/stdc++.h>
using namespace std;
int main(){
	string str="abcabcabcabc";
	int len=str.size();
	int p[len];
	p[0]=0;
	int j=0,i=1;
	while(i<len){
		if(str[j]==str[i]){
			p[i]=j+1;
			i++;j++;
		}
		else{
			if(j!=0){
				j=p[j-1];
			}
			else{
				p[i]=0;
				i++;
			}		
		}
	}
	for(auto x:p){
		cout<<x<<" ";
	}	
	cout<<"\n";
	return 0;
}
