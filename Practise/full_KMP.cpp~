#include<bits/stdc++.h>
using namespace std;
void KMPfailure_fxn(string text,int *p){
	p[0]=0;
	int i=1,j=0;
	int len=text.length();
	while(i<len){
		if(text[i]==text[j]){
			p[i]=j+1;
			i++;j++;
		}
		else{
			if(j==0){
				p[i]=0;
				i++;
			}
			else{
				j=p[j-1];
			}
		}
	}
}
int main(){
	vector<int>v;
	string text,fin;
	cout<<"Enter the text\n";
	cin>>text;
	printf("Enter the string to be searched for\n");
	cin>>fin;
	int lenText=text.length();
	int lenFin=fin.length();
	int p[lenFin];
	KMPfailure_fxn(fin,p);
	// Searching a txt for occurence of pattern fin
	int i=0,j=0;
	while(i<lenText){
		if(text[i]==fin[j]){
			i++;j++;
			if(j==lenFin){
				v.push_back(i-j);
				j=p[j-1];
			}
		}
		else{
			if(j==0){
			    //No prefix information ==> slide P up 1 position
				i++;   //SLide 1 character over
				j=0;
			}
			else{
				int k=p[j-1]; // Max Overlap (= length of matching prefix)  using KMP Failure fxn here...
				j=k;	// Restart matching at character after matching prefix
				i=(i-j);  // Shift pattern (i-j) characters
			}
		}
	}
	printf("No. of matches:- %d\n",v.size());
	for(auto x:v){
		cout<<x<<endl;
	}
	return 0;
}
