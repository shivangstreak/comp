#include<bits/stdc++.h>
using namespace std;
int c[55];
int main(){
	int n,t;scanf("%d%d",&n,&t);
	string str;cin>>str;
	for(int i=0;i<t;i++){
		for(int i=0;i<n;i++){
			if(i==n-1){
				c[i]=-1;
				continue;
			}
			if(str[i]=='B' && str[i+1]=='G'){
				c[i]=1;
			}
			else{
				c[i]=-1;
			}
		}
		for(int i=0;i<n-1;i++){
			if(c[i]==1){
				swap(str[i],str[i+1]);
			}
		}	
	}
	cout<<str<<"\n";
	return 0;
}
