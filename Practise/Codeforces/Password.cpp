#include<bits/stdc++.h>
using namespace std;
int p[1000005];
int main(){
	string str;cin>>str;
	p[0]=0;
	int j=0,i=1;
	int len=str.size();
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
	int yy=len-1;
	int find=p[len-1];
	int y,dd=len-find;
	if(find==0){
		printf("Just a legend\n");
	}	
	else{
			int flag=0;
			for(int j=0;j<yy;j++){
				if(p[j]==find){
					cout<<str.substr(0,find)<<endl;
					flag=1;
					break;
				}
			}
			if(flag==1){
				return 0;
			}
			else{
				dd=p[find-1];
				if(dd!=0){
					cout<<str.substr(0,dd)<<endl;
					flag=1;
				}
			}
		if(flag==0){
			printf("Just a legend\n");
		}
	}
	return 0;
}

/*
Using Z-Algo
Lastly, to solve Problem B of Beta Round 93, we simply compute Z for the given string S, then iterate from i to n - 1. If Z[i] = n - i then we know the suffix from S[i] is a prefix, and if the largest Z value we've seen so far is at least n - i, then we know some string inside also matches that prefix. That gives the result.

int maxz = 0, res = 0;
for (int i = 1; i < n; i++) {
  if (z[i] == n-i && maxz >= n-i) { res = n-i; break; }
  maxz = max(maxz, z[i]);
}
*/
