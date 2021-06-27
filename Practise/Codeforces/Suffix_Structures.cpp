#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL);
int c1[26],c2[26];
int main(){
	faster
	string s,t;cin>>s>>t;
	for(auto x:s){
		c1[x-'a']++;
	}
	for(auto x:t){
		c2[x-'a']++;
	}
	int flag=0;
	for(int i=0;i<26;i++){
		//cout<<'a'+i<<" "<<c1[i]<<" "<<c2[i]<<endl;
		if(c1[i]<c2[i]){
			flag=1;
			break;
		}
	}	
	if(flag==1){
		printf("need tree\n");
		return 0;
	}
	if(s.size()==t.size()){
		for(int i=0;i<26;i++){
			if(c1[i]!=c2[i]){
				flag=1;
				break;
			}
		}
		if(flag==0){
			printf("array\n");
			return 0;
		}
	}
	else{
		int len1=s.size(),len2=t.size();
		int j=0;
		for (int i=0;(i<len1)&&(j<len2); i++)
		       if (t[j] == s[i])
			 j++;
		if(j==len2){
			printf("automaton\n");
			return 0;
		}
		else{
			printf("both\n");
		}
	}
	return 0;
}
