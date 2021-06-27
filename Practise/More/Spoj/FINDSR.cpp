#include<bits/stdc++.h>
using namespace std;
int p[100005];
string str;
int len;
void prefix_table(){
	int i=1,j=0;
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
}
int main(){
	while(true){
		cin>>str;
		if(str=="*"){
			break;
		}
		len=str.size();
		prefix_table();
		if(len%(len-p[len-1])==0){   // you can also add p[len-1]!=0 inside if statement though this code has been accepted
			cout<<len/(len-p[len-1])<<"\n";
		}
		else{
			cout<<"1\n";
		}
	}
	return 0;
}
