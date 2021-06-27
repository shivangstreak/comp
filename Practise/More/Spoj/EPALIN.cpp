#include<bits/stdc++.h>
using namespace std;
int n;
vector<int> prefix(string s) {
	vector<int> p(s.length());
	p[0]=0;
	int i=1,j=0;
	while(i<s.size()){
		if(s[i]==s[j]){
			p[i]=j+1;
			i++;
			j++;
		}
		else{
			if(j!=0){
				j=p[j-1];
			}
			else{
				p[i]=0;i++;	
			}
		}
	}
	return p;
}
void solve(string s, string ans, string rev){
	vector<int> pre = prefix(s);
	int maxu = 0;
	maxu = pre[pre.size()-1];
	int ind = (maxu);
	for(int i = maxu; i < n; i++) ans += rev[i];
	cout<<ans<<"\n"; 
}
char temp[10000000];
int main(){
	while(scanf("%s",temp) != EOF){
		string s = (string)temp;
		string p="";
		p+=s;
		n=s.length();
		reverse(p.begin(), p.end());
		p += "#";
		p += s;
		solve(p, s, p);
	}
	return 0;
}
