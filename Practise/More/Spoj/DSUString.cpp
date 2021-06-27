#include<bits/stdc++.h>
using namespace std;
struct node{
	int i;
	string str;
	node(int i1,string s1){
		str=s1;
		i=i1;
	}
};
int root(){
	
}
void initialize(vector<node>&v,int size[],int n){
	for(int i=0;i<n;i++){
		string str1;cin>>str1;
		v.push_back(node(i,str1));	
		size[i]=1;
	}
}
bool is_same_subset(){
	int root_A=root();
	int root_B=root();
	if(root_A==root_B){
		return true;
	}
	else{
		return false;
	}
}
int main(){
	int n;scanf("%d",&n);
	int size[n];
	vector<node>v;
	initialize(v,size,n);
	return 0;
}
