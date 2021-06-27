#include<bits/stdc++.h>   // NOTE: Whenever very large input number such as  1000 digits use string and then convert it to insigned long long 
using namespace std;
#define MAX 6000
#define ll unsigned long long
int main(){
    ll int j,n,i,t,flag,fib[MAX];
    char s[1001];
    cin>>t;
    while(t--){
        flag=0;
        scanf("%s",s);j=0;n=0;
        while(s[j]!='\0'){
            n=n*10;
            n=n+(s[j]-'0');
            j++;
        }
        fib[0]=0;
        fib[1]=1;
        if((n==0)||(n==1)){
            flag=1;
        }
        for(j=2;(j<MAX)&&(flag==0);j++)
        {
            fib[j]=fib[j-1]+fib[j-2];
            if(fib[j]==n)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            printf("YES\n");
        }
        else
        {
             printf("NO\n");
        }
    }
return 0;
}
 
