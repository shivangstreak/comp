#include<bits/stdc++.h>
using namespace std;
#define MAX(a,b) (a>b)?a:b
int a[100000]={0};
unsigned long int s=0,i;
unsigned long int rec(unsigned long int n){
         s=0;
         if(n<12)
                 return n;
         else if(n>=0&&n<=100000){
              if(a[n])
              return a[n];
              else
              {
                  s=rec(n/2)+rec(n/3)+rec(n/4);
                  a[n]=MAX(s,n);
                  return a[n];
              }
         }
         else
         {
             s=rec(n/2)+rec(n/3)+rec(n/4);
             return MAX(s,n);
         }
}
int main(){
    unsigned long int n;
    while(scanf("%lu",&n)!=EOF){
                    printf("%lu\n",rec(n));
    }
    return 0;
}
 
