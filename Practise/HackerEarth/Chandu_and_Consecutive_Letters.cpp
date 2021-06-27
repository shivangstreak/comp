#include<bits/stdc++.h>
using namespace std;
int main(){
	int t;scanf("%d",&t);
	while(t--){
		string str,str1="";cin>>str;
		queue<char>q;
		for(auto x:str){
			q.push(x);
		}
		while(q.empty()==false){
			if(q.front()==*str1.rbegin()){
				q.pop();
			}
			else{
				str1+=q.front();
				q.pop();
			}
		}
		cout<<str1<<endl;
	}
	return 0;
}
