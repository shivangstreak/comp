#include<bits/stdc++.h>
using namespace std;
#define ll long long
int c[26];
int main(){	
	char str[1005];
	scanf("%s",str);
	int len=strlen(str);
	int k=0;
	for(int i=0;i<len;i++){
		c[str[i]-'a']++;
	}
	for(int i=0;i<len;i++){
		if(c[str[i]-'a']%2==1){
			k++;
		}
	}
	if(k<=1){
		printf("First\n");
	}
	else{
		if(k%2==1){
			printf("First\n");
		}
		else{
			printf("Second\n");
		}
	}
	return 0;
}
