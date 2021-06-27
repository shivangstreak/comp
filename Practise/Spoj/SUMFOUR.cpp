#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
int A[4005];
int B[4005];
int C[4005];
int D[4005];
int v1[10000001];
int v2[10000001];
int main(){
	int n;scanf("%d",&n);
	int len1=0,len2=0;
	for(int i=0;i<n;i++){
		scanf("%d",&A[i]);	
		scanf("%d",&B[i]);
		scanf("%d",&C[i]);
		scanf("%d",&D[i]);
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			v1[len1]=A[i]+B[j];
			len1++;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			v2[len2]=-1*(C[i]+D[j]);
			len2++;
		}
	}
	sort(v1,v1+len1);
	sort(v2,v2+len2);
	int low,high;
	int sum=0;
	int i=0;
	while(i<len1){
		int count1=0;
		int y=v1[i];
		cout<<y<<" ";
		while(v1[i]==y && i<len1){
			count1++;
			i++;
		}		
		low=lower_bound(v2,v2+len2,y)-v2;
		high=upper_bound(v2,v2+len2,y)-v2;
		cout<<low<<" "<<high<<endl;
		sum+=count1*(high-low);
	}
	printf("%d\n",sum);
	return 0;
}
