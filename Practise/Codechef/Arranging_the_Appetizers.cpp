#include<bits/stdc++.h>
using namespace std;
int f[17];
int n;
int flip(int x){   // Function to rotate like 1010 becomes 0101 ..
	x=x&f[n];
	int s=0&f[n];
	int j=n-1;
	for(int i=0;i<n;i++){
		if(x&(1<<i)){
			s=s|(1<<j);
		}
		j--;
	}
	return s;
}
int main(){
	int q=0;
	for(int i=1;i<=16;i++){
		q+=1<<(i-1);
		f[i]=q;
	}
	int t;scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		string str;cin>>str;
		string str1="";
		for(int i=0;i<str.size();i++){
			str1+=str[flip(i)];
		}
		cout<<str1<<"\n";
	}
	return 0;
}
