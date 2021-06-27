#include<bits/stdc++.h>
using namespace std;
int A[100005];
string str1;
int len;
void makeprefix_table(string str){
	A[0]=0;
	int i=1,j=0;
	while(i<len){
		if(str[j]==str1[i]){
			A[i]=j+1;
			j++;i++;
		}
		else{
			if(j!=0){
				j=A[j-1];
			}
			else{
				A[i]=0;
				i++;
			}
		}
	}
}
int main(){
	int n,m;cin>>n>>m;
	str1="";	
	string str;
	while(n--){
		cin>>str;
		str1+=str;
	}	
	int N=str1.size();
	while(m--){
		int c=0;
		cin>>str;
		memset(A,0,sizeof(A));
		len=str.size();
		makeprefix_table(str);
		int i=0,j=0; //i is index of main string //j is index of pattern
		while(i<N){
			if(str[j]==str1[i]){
				i++;j++;
			}
			if(j==len){
				c++; // Desierd Pattern found at i-j;
				//cout<<str<<" found at "<<i-j<<"\n";			
				j = A[j-1];
			}
			else if(i<N && str[j]!=str1[i]){
				if(j!=0)
         				j=A[j-1];
        			else
         				i=i+1;
			}
		}
		cout<<c<<"\n";
	}
	return 0;
}
