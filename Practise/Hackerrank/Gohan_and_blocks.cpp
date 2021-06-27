#include<bits/stdc++.h>
using namespace std;
set<string>S;
int c=0;
string str;
void f(stack<char>s,string g,int p){
	if(p==str.size()){
		while(s.empty()==false){
			g+=s.top();
			s.pop();
		}
		S.insert(g);
		if(g==str){
			c++;
		}
	}
	else{
		s.push(str[p]);
		f(s,g,p+1);
		s.pop();
		if(s.empty()==false){
			char ch=s.top();
			s.pop();
			f(s,g+ch,p);
		}
	}
}
int main() {
	cin>>str;
	stack<char>s;
	f(s,"",0);
	cout<<c<<" "<<S.size();
    return 0;
}

