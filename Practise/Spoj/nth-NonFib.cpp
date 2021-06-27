//Complexity: O(log n)
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	do{
	scanf("%d",&n);
	 int ans;
	 int a=1,b=2,c=3;
              while(n>0)
              {
               a=b;
               b=c;
               c=a+b;
               n-=(c-b-1);
              }
              n+=(c-b-1);
              ans=b+n;
        cout<<ans<<endl;      
	}while(n!=-1);
		return 0;
} 
            
