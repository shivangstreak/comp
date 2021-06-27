#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
int main(){
	char S[N],T[N];
	scanf("%s%s",S,T);
	int lens=strlen(S),lent=strlen(T);
	int i=0,j=0;
	int ans=0;
	while(i<lens && j<lent){
		if(S[i]==T[j]){
			ans++;
			i++;
		}
		j++;
	}
	printf("%d\n",ans);
	return 0;
}
