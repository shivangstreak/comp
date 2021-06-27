#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,k,l,q;scanf("%d%d%d%d",&n,&k,&l,&q);
	map<string,string>m;
	while(n--){
		string str,str1="";cin>>str;
		for(int i=0;i<k;i++){
			int d;scanf("%d",&d);
			str1+=d+'0';
		}
		m[str1]=str;
	}
	while(q--){
		string str3="";
		for(int i=0;i<k;i++){
			int d;scanf("%d",&d);
			str3+=d+'0';
		}
		if(m[str3]==""){
			printf("You cant fool me :P\n");
		}
		else{
			cout<<m[str3]<<"\n";
		}
	}
	return 0;
}
