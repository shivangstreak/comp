#include<bits/stdc++.h>
using namespace std;
int main() {
	string str="",str1="";
	int m,s;scanf("%d%d",&m,&s);
	if(s==0 && m==1){
		printf("0 0\n");
		return 0;
	}
	if(s==0 && m>1){
		printf("-1 -1\n");
		return 0;
	}
	for(int i=0;i<m;i++){
		str+=min(9,s)+'0';
		s-=min(9,s);
	}
	if(s>0){
		printf("-1 -1\n");
		return 0;
	}
	str1=str;
	reverse(str1.begin(),str1.end());
	int i;
	for(i=0;i<m;i++){
		if(str1[i]!='0'){
			break;
		}
	}
	str1[i]--;
	str1[0]++;	
	cout<<str1<<" "<<str<<"\n";
}
