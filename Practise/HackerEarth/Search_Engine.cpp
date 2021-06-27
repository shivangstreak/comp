#include<bits/stdc++.h>  // Trie...
using namespace std;
const int N=1e6+5;
struct node{
	int val;
	node *children[26];
};
struct trie{
	node *root;
};
node *getNode(){
	node *temp=NULL;
	temp=new node();
	if(temp){
		temp->val=-1;
		for(int i=0;i<26;i++)
			temp->children[i]=NULL;
	}
	return temp;
}
void init(trie *root){
	root->root=getNode();
}
void insert(trie *root,char *str,int d){
	node *temp=NULL;
	temp=root->root;
	int index,len=strlen(str);
	for(int i=0;i<len;i++){
		index=(int)str[i]-(int)'a';
		if(temp->children[index]==NULL){
			temp->children[index]=getNode();
		}
		if(temp->children[index]->val<d){
			temp->children[index]->val=d;
		}
		temp=temp->children[index];
	}
	if(temp->val<d){
		temp->val=d;
	}
}
int search(trie *root,char *str){
	node *temp=NULL;
	temp=root->root;
	int index,len=strlen(str);
	for(int i=0;i<len;i++){
		index=(int)str[i]-(int)'a';
		if(temp->children[index]==NULL){
			return -1;
		}
		else{
			temp=temp->children[index];
		}
	}
	return temp->val;
}
int main(){
	int n,q,d;scanf("%d%d",&n,&q);
	char str[N];
	trie root;
	init(&root);
	while(n--){
		scanf("%s%d",str,&d);
		insert(&root,str,d);
	}
	while(q--){
		scanf("%s",str);
		printf("%d\n",search(&root,str));
	}
	return 0;
}
