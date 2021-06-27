#include<bits/stdc++.h>
using namespace std;
#define ll long long
int a[3005];
int main(){
	int n,m;scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d",&a[i]);
	}
	sort(a,a+m);
	/*printf("After sorting\n");
	for(int i=0;i<m;i++){
		cout<<a[i]<<" ";
	}
	printf("\n");*/
	if(a[0]==1 || a[m-1]==n){
		printf("NO\n");
	}
	else{
		int flag=1,flag1=1;
		for(int i=0;i<m-2;i++){
			flag1=0;
			int y=a[i];
			//cout<<y<<" "<<a[i+1]<<" "<<a[i+2]<<endl;
			if(y+1==a[i+1] && y+2==a[i+2]){
				flag=0;
				break;
			}
		}
		if(flag1==1 && m==3){
			int y=a[0];
			if(y+1==a[1] && y+2==a[2]){
				flag=0;
			}			
		}
		if(flag==1){
			printf("YES\n");
		}
		else{
			printf("NO\n");
		}
	}
	return 0;
}
