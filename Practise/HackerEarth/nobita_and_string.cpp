#include <bits/stdc++.h>
using namespace std;
int main(){
int t;scanf("%d\n",&t);
	char name[100005];
	while(t--){
		string str;
		getline(cin,str);
		int len=str.size();
		vector<string>v;
		string str1="";
		for(int i=0;i<len;i++){
			if(str[i]==' '){
				v.push_back(str1);
				str1="";
				continue;
			}
			str1+=str[i];
			if(i==len-1){
				v.push_back(str1);
			}
		}
		int i=0,j=v.size()-1;
		while(i<j){
			swap(v[i],v[j]);
			i++;
			j--;
		}
		for(auto x:v){
			cout<<x<<" ";
		}
		cout<<"\n";
	}
    return 0;
}

