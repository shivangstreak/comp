#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define ll long long int
#define II pair<int,int>
#define faster std::ios::sync_with_stdio(false);cin.tie(NULL)
string str[105];
int g[26][26];
string a,b;
int lena,lenb;
bool cycle;
bool vis[26],recurr[26];
stack<int>q;
void dfs(int u){
	if(vis[u]==true){
		if(recurr[u]==true){
			cycle=true;   // Trying to detect any cycle!!!
			return;
		}
	}
	else{
		vis[u]=true;
		recurr[u]=true;
		for(int j=0;j<26;j++){
			if(g[u][j]==1){
				dfs(j);
			}
		}
		recurr[u]=false;
		q.push(u);
	}	
}
int main(){
	faster;
	int n;cin>>n;
	int indx;
	cycle=false;
	for(int i=0;i<n;i++)
		cin>>str[i];
	for(int i=1;i<n;i++){
		a=str[i-1];
		b=str[i];
		lena=a.size();lenb=b.size();
		indx=0;
		while(indx<lena && indx<lenb && a[indx]==b[indx]){
				indx++;
		}
		if(indx==lenb && indx!=lena){
			printf("Impossible\n");
			return 0;
		}
		if(indx<lenb && indx<lena)
			g[a[indx]-'a'][b[indx]-'a']=1;
		//cout<<a[indx]<<" "<<b[indx]<<endl;
	}
	for(int i=0;i<26;i++){
		if(vis[i]==false){
			dfs(i);
			if(cycle==true){
				printf("Impossible\n");
				return 0;		
			}
		}
	}
	/*for(auto x:q){
		cout<<char(x+'a');
	}
	cout<<endl;*/
	int top;
	while(q.empty()==false){
		top=q.top();
		q.pop();
		cout<<char(top+'a');
	}
	cout<<"\n";
	return 0;
}
