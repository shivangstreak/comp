#include<bits/stdc++.h>  // Using it masking to generate all susets of a given set...
using namespace std;
int main(){
	int a[]={1,2,3,4,5};
	int mask=1<<5;
	int i=0;
	while(i<mask){
		for(int j=0;j<5;j++){
			if(i&(1<<j) ){
				cout<<a[j]<<" ";
			}
		}
		printf("\n");
		i++;
	}
	return 0;
}
