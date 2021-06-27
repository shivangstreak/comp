#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;cin>>t;
    while(t--){
    	string str1,str2;cin>>str1;
		int i=0,j=0;
		while(i<str1.size()){
			if(str1[i]==str1[i+1]){
				i++;continue;
			}
			else{
				str2+=str1[i];
				i++;
			}
		}
		cout<<str2<<endl;
    }
    return 0;
}

