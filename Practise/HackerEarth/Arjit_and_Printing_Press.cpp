#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		string a,b;cin>>a>>b;
		int lena=a.size(),lenb=b.size();
		int c[26];memset(c,0,sizeof(c));
		for(int i=0;i<lenb;i++){
			c[b[i]-'a']++;
		}
		int j=0;
		vector<int>v;
		for(int i=0;i<26;i++){
			if(c[i]>0){
				v.push_back(i);
			}
		}
		int vlen=v.size();
		for(int i=0;i<lena;i++){
			if(j==v.size()){
				break;
			}
			if(a[i]>v[j]+'a'){
				a[i]=v[j]+'a';
				c[v[j]]--;
				if(c[v[j]]==0){
					j++;
				}
			}
		}
		cout<<a<<endl;
	}
	return 0;
}
