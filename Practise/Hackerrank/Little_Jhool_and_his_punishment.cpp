#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		int n,b,g;scanf("%d%d%d",&n,&b,&g);
		if(b==g){
			printf("The teacher wins!\n");
			continue;			
		}
		string str="";
		int i=0;
		if(g<b){
			str+='0';
			g--;
		}
		else{
			str+='1';
			b--;
		}
		int flag=0;
		while(b>0 || g>0){
			if(flag==0){
				if(str[i]=='0'){
					if(b!=0){
						str+='1';
						b--;
					}
					else{
						str+='0';
						g--;
					}
				}
				else{
					if(g!=0){
						str+='0';
						g--;
					}
					else{
						str+='1';
						b--;
					}					
				}	
				flag=1;
			}
			else{
				if(str[i]=='0'){
					if(g!=0){
						str+='0';
						g--;
					}
					else{
						str+='1';
						b--;
					}
				}
				else{
					if(b!=0){
						str+='1';
						b--;
					}
					else{
						str+='0';
						g--;
					}					
				}
				flag=0;				
			}
		}
		int l=str.size();
		int c1=0,c2=0;
		for(int i=0;i<l-1;i++){
			if(str[i]==str[i+1]){
				c1++;
			}
			else{
				c2++;
			}
		}
		if(c1>c2){
			printf("Little Jhool wins!\n");
		}
		else{
			printf("The teacher wins!\n");
		}
	}
	return 0;
}
