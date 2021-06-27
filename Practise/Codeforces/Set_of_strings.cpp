#include<bits/stdc++.h>
using namespace std;
int main(){
	int k;scanf("%d",&k);
	string str;cin>>str;
	int len=str.size();
	if(len<k){
		printf("NO\n");
		return 0;
	}
	if(k==1){
		printf("YES\n");
		cout<<str<<"\n";
	}
	else{
		int a[26];
		int y=0;
		memset(a,0,sizeof(a));
		for(int i=0;i<len;i++){
			if(a[str[i]-'a']==0){
				a[str[i]-'a']=1;
				y++;
			}
		}
		if(y<k){
			printf("NO\n");
			return 0;
		}
		else{
			int l[26];
			memset(l,0,sizeof(l));
			printf("YES\n");
			int i=0,j=0;
			while(j<k){
				string str1="";
				if(i<len && l[str[i]-'a']==0){
					str1+=str[i];
					l[str[i]-'a']=1;
					i++;
				}
				for(;i<len;i++){
					if(l[str[i]-'a']==1){
						str1+=str[i];
					}
					else{
						break;
					}
				}
				cout<<str1;
				if(j!=k-1){
					cout<<"\n";
				}
				j++;
			}
			for(;i<len;i++){
				cout<<str[i];
			}
		}
	}
	return 0;
}
