#include<bits/stdc++.h>
using namespace std;
int p[1000005];
int main(){
	int t;scanf("%d",&t);
	for(int y=1;y<=t;y++){
		int len;scanf("%d",&len);
		string str;cin>>str;
		p[0]=0;	
		int i=1,j=0;
		while(i<len){
			if(str[i]==str[j]){
				p[i]=j+1;	
				i++;j++;
			}
			else{
				if(j==0){
					p[i]=0;
					i++;
				}
				else{
					j=p[j-1];
				}
			}
		}
		printf("Test case #%d\n",y);
		for(int i=1;i<len;i++){
			int temp_len=i+1;			
			if(p[i]!=0 && temp_len%(temp_len-p[i])==0){
				printf("%d %d\n",i+1,temp_len/(temp_len-p[i]));
			}
		}
		printf("\n");
	}
	return 0;
}
