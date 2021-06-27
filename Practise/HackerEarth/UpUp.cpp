#include<bits/stdc++.h>
using namespace std;
const int N=3e4+5;
int main(){
	char str[N];
	scanf("%[^\n]%*c",str);
	int len=strlen(str);
	for(int i=0;i<len;i++){
		if(i==0 && 'a'<=str[i] && str[i]<='z'){
			str[i]-=32;
			continue;
		}
		if(str[i-1]==' ' && 'a'<=str[i] && str[i]<='z'){
			str[i]-=32;
			continue;
		}
	}
	printf("%s\n",str);
	return 0;
}
