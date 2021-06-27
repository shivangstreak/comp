#include<bits/stdc++.h> // Time Complexity is O(n*log(n)*log(n)) also LCP array construction in O(n) time
using namespace std;
const int N=1e6+5;
struct suffix{
	int index;
	int rank[2];
};
bool cmp(struct suffix A,struct suffix B){
	return (A.rank[0]==B.rank[0]?((A.rank[1]<B.rank[1])?true:false):(A.rank[0]<B.rank[0])?true:false);
}
suffix suf[N];
int intArr[N];
int suffixArray[N];
int main(){
	string str;cin>>str;
	int len=str.length();
	for(int i=0;i<len;i++){
		suf[i].index=i;
		suf[i].rank[0]=str[i]-'a';
		if(i+1<len){
			suf[i].rank[1]=str[i+1]-'a';
		}
		else{
			suf[i].rank[1]=-1;
		}
	}
	sort(suf,suf+len,cmp);
	for(int k=4;k<2*len;k=k*2){
		int rank=0;
		int prev_rank=suf[0].rank[0];
		suf[0].rank[0]=rank;
		intArr[suf[0].index]=0;
		for(int i=1;i<len;i++){
			if(prev_rank==suf[i].rank[0] && suf[i-1].rank[1]==suf[i].rank[1]){
				prev_rank=suf[i].rank[0];
				suf[i].rank[0]=rank;
			}
			else{
				prev_rank=suf[i].rank[0];
				suf[i].rank[0]=++rank;
			}
			intArr[suf[i].index]=i;
		}
		for(int i=0;i<len;i++){
			int nextIndex=suf[i].index+k/2;
			if(nextIndex<len){
				suf[i].rank[1]=suf[intArr[nextIndex]].rank[0];
			}
			else{
				suf[i].rank[1]=-1;
			}
		}
		sort(suf,suf+len,cmp);
	}
	for(int i=0;i<len;i++){
		suffixArray[i]=suf[i].index;
	}
	/*cout<<"Suffix array is:-\n";
	for(int i=0;i<len;i++){
		cout<<suffixArray[i]<<" ";
	}
	printf("\n");*/

	// LCP Array Construction
	vector<int>lcp(len,0);
	vector<int>Rank(len,0);
	for(int i=0;i<len;i++){
		Rank[suffixArray[i]]=i;
	}
	int k=0;
	for(int i=0;i<len;i++,k?k--:0){
		if(Rank[i]==len-1){
			k=0;
			continue;
		}
		int j=suffixArray[Rank[i]+1];
		while(j+k<len && i+k<len && str[i+k]==str[j+k]){
			k++;
		}
		lcp[Rank[i]]=k;
	}
	/*printf("LCP Array is:-\n");
	for(int i=0;i<len;i++){
		cout<<lcp[i]<<" ";
	}
	printf("\n");*/
	int mx=INT_MIN;
	for(int i=0;i<len;i++){
		if(lcp[i]>mx){
			mx=lcp[i];
		}
	}
	printf("%d\n",mx);
	return 0;
}
